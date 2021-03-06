#!/usr/bin/python

import avango
import avango.script
from avango.script import field_has_changed
import avango.gua
from examples_common.GuaVE import GuaVE

# STEREO_MODE = avango.gua.StereoMode.ANAGLYPH_RED_CYAN
# STEREO_MODE = avango.gua.StereoMode.ANAGLYPH_RED_GREEN
# STEREO_MODE = avango.gua.StereoMode.SIDE_BY_SIDE
STEREO_MODE = avango.gua.StereoMode.CHECKERBOARD

class TimedRotate(avango.script.Script):
  TimeIn = avango.SFFloat()
  MatrixOut = avango.gua.SFMatrix4()

  @field_has_changed(TimeIn)
  def update(self):
    self.MatrixOut.value = avango.gua.make_rot_mat(self.TimeIn.value*2.0, 0.0, 1.0, 0.0)

def start():

  # setup scenegraph
  graph = avango.gua.nodes.SceneGraph(Name = "scenegraph")

  loader = avango.gua.nodes.TriMeshLoader()
  monkey = loader.create_geometry_from_file("monkey", "data/objects/monkey.obj", "data/materials/Stones.gmd", avango.gua.LoaderFlags.DEFAULTS)

  light = avango.gua.nodes.PointLightNode(Name = "light", Color = avango.gua.Color(1.0, 1.0, 1.0))
  light.Transform.value = avango.gua.make_trans_mat(1, 1, 2) * avango.gua.make_scale_mat(15, 15, 15)

  left_eye = avango.gua.nodes.TransformNode(Name = "left_eye")
  left_eye.Transform.value = avango.gua.make_trans_mat(-0.1, 0.0, 0.0)

  right_eye = avango.gua.nodes.TransformNode(Name = "right_eye")
  right_eye.Transform.value = avango.gua.make_trans_mat(0.1, 0.0, 0.0)

  head = avango.gua.nodes.TransformNode(Name = "head")
  head.Transform.value = avango.gua.make_trans_mat(0.0, 0.0, 3.5)
  head.Children.value = [left_eye, right_eye]

  screen = avango.gua.nodes.ScreenNode(Name = "screen", Width = 4, Height = 3)
  screen.Children.value = [head]

  graph.Root.value.Children.value = [monkey, light, screen]

  # setup viewing
  width = 1024
  height = 768
  eye_size = avango.gua.Vec2ui(width, height)
  window_size = avango.gua.Vec2ui(width, height)
  left_pos = avango.gua.Vec2ui(0, 0)
  right_pos = avango.gua.Vec2ui(0, 0)

  if STEREO_MODE == avango.gua.StereoMode.SIDE_BY_SIDE:
    right_pos.x = width + 1
    window_size.x *= 2

  pipe = avango.gua.nodes.Pipeline(Camera = avango.gua.nodes.Camera(LeftEye = "/screen/head/left_eye",
                                                                    RightEye = "/screen/head/right_eye",
                                                                    LeftScreen = "/screen",
                                                                    RightScreen = "/screen",
                                                                    SceneGraph = "scenegraph"),
                                   Window = avango.gua.nodes.Window(Size = window_size,
                                                                    LeftPosition = left_pos,
                                                                    LeftResolution = eye_size,
                                                                    RightPosition = right_pos,
                                                                    RightResolution = eye_size,
                                                                    StereoMode = STEREO_MODE),
                                   LeftResolution = eye_size,
                                   RightResolution = eye_size,
                                   EnableStereo = True)

  #setup viewer
  viewer = avango.gua.nodes.Viewer()
  viewer.Pipelines.value = [pipe]
  viewer.SceneGraphs.value = [graph]

  monkey_updater = TimedRotate()

  timer = avango.nodes.TimeSensor()
  monkey_updater.TimeIn.connect_from(timer.Time)

  monkey.Transform.connect_from(monkey_updater.MatrixOut)

  guaVE = GuaVE()
  guaVE.start(locals(), globals())

  viewer.run()


if __name__ == '__main__':
  start()

