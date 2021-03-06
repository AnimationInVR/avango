# -*- Mode:Python -*-

##########################################################################
#                                                                        #
# This file is part of AVANGO.                                           #
#                                                                        #
# Copyright 1997 - 2010 Fraunhofer-Gesellschaft zur Foerderung der       #
# angewandten Forschung (FhG), Munich, Germany.                          #
#                                                                        #
# AVANGO is free software: you can redistribute it and/or modify         #
# it under the terms of the GNU Lesser General Public License as         #
# published by the Free Software Foundation, version 3.                  #
#                                                                        #
# AVANGO is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU Lesser General Public       #
# License along with AVANGO. If not, see <http://www.gnu.org/licenses/>. #
#                                                                        #
##########################################################################

import avango.script
import avango.osg
import avango.display
import avango.utils
import os


import avango.display

from avango.display import *

import math
import re


class StatsViewer(avango.script.Script):
    Views = avango.osg.viewer.MFView()
    StatsNum = avango.SFInt()

    def __init__(self):
        self.super(StatsViewer).__init__()

    def evaluate(self):
        for view in self.Views.value:
            view.StatsMode.value = self.StatsNum.value
            
class MatrixLeftTransformer(avango.script.Script):
    
    MatrixIn = avango.osg.SFMatrix()
    MatrixOut = avango.osg.SFMatrix()
    MatrixLeftMul = avango.osg.SFMatrix()
    
    def __init__(self):
        self.super(MatrixLeftTransformer).__init__()
        self.MatrixLeftMul.value = avango.osg.make_trans_mat(0,0,0);
        
    def evaluate(self):
        self.MatrixOut.value = self.MatrixLeftMul.value * self.MatrixIn.value
        

class LShape(avango.display.Display):

    def __init__(self, inspector, options):
        super(LShape, self).__init__("LShape", inspector)
        
        print str(options)
        
        if "twopipe" in options:
            two_view_walls = [":0.0", ":0.1"]
            twopipe = True
        else:
            two_view_walls = [":0.0", ":0.0"]
            twopipe = False

        # Viewer 1
        window1 = self.make_window(0, 0, 1280, 1024, 6, 2.4, True, two_view_walls[0])
        window1.Name.value = "1"
        self.add_window(window1, avango.osg.make_trans_mat(0., 1.2, -2.4), 0)

        # Viewer 2
        if not twopipe:
            xpos = 1280
        else:
            xpos = 0
        window2 = self.make_window(xpos, 0, 1280, 1024, 6, 2.4, True, two_view_walls[1])
        window2.Name.value = "2"
        #self.add_window(window2, avango.osg.make_trans_mat(0., 1.2, -2.4), 1)
	self.add_window(window2, avango.osg.make_rot_mat(math.radians(-90),1,0,0) * avango.osg.make_trans_mat(0, 0, -1.2), 0)

        #store the created views. Needed for the stats display
        self._views = []

        #create a device service
        self._device_service = avango.daemon.DeviceService()

        # Users
        user1 = avango.display.nodes.User()
        self.add_user(user1)
        #user2 = avango.display.nodes.User()
        #self.add_user(user2)

        # Connect head-tracking
        #view1_yellow_glasses = self.make_glasses("ve-dtrack-head4", avango.osg.Vec3(-0.074, -0.018, 0.025))
        view1_yellow_glasses = self.make_glasses("ve-dtrack-xpand1", avango.osg.Vec3(-0.0825, 0.0, -0.045))
        user1.Matrix.connect_from(view1_yellow_glasses.Matrix)
        self.user1_matrix_mul = MatrixLeftTransformer()
        user1.ViewerMatrix.connect_from(self.user1_matrix_mul.MatrixOut)
        self.keep_alive(view1_yellow_glasses)
        
        
        #blue glasses do not work properly. Use purple glasses instead
        #view2_purple_glasses = self.make_glasses("ve-dtrack-xpand2", avango.osg.Vec3(0.12, 0.043, 0.0 ))
        #user2.Matrix.connect_from(view2_purple_glasses.Matrix)
        #self.user2_matrix_mul = MatrixLeftTransformer()
        #user2.ViewerMatrix.connect_from(self.user2_matrix_mul.MatrixOut)
        #self.keep_alive(view2_purple_glasses)
        

        self._wiimote_config = {}
        self._wiimote_config["wiimote1"] = ["ve-dtrack-atek",     avango.osg.Vec3( 0.045, 0.0,  0.022)]
        self._wiimote_config["wiimote2"] = ["ve-dtrack-reddot",   avango.osg.Vec3(-0.05 , 0.0,  0.031)]
        self._wiimote_config["wiimote3"] = ["ve-dtrack-logitech", avango.osg.Vec3(-0.04 , 0.0, -0.025)]
        self._wiimote_config["wiimote4"] = ["ve-dtrack-raytac",   avango.osg.Vec3( 0.068, 0.02, 0.035)]
        
        self.icone_view = None
        
    def make_view(self, subdisplay, display_view = None):
        print "LShape::make_view"
        if not display_view:
            display_view = avango.display.nodes.LShapeView()
            self.icone_view = display_view
        num = 0
        for window, transform, current_user in self._windows:
            
            eye_offset = 0.
            if window.StereoMode.value != avango.osg.viewer.stereo_mode.STEREO_MODE_NONE:
                eye_offset = 0.03

            camera, view = self.make_camera_with_viewport(
                display_view, eye_offset, transform, window, num)
            camera.EyeTransform.connect_from(self._users[current_user].Matrix)

            user_selector = ViewUserSelector(UserMatch=current_user+1)
            user_selector.ViewIn.value = view
            user_selector.UserSelector.connect_from(display_view.UserSelector)
            self.keep_alive(user_selector)
            self.connect_view_field(user_selector.ViewOut)
            
            num += 1
            self.view_created(camera, view, subdisplay)
            
            
        if self._inspector and len(self._inspector.Children.value) == 0:
            # FIXME this should use a proper aggregation node
            converter = avango.utils.nodes.SFNode2MFContainerConverter()
            converter.Input.connect_from(display_view.Root)
            self._inspector.Children.connect_from(converter.Output)

        return display_view
    
    def make_camera_with_viewport(self, display_view, eye_offset, screen_transform, window, num):
        splitscreen_handling = ViewportConverter()
        splitscreen_handling.ViewportIn.connect_from(display_view.Viewport)
        splitscreen_handling.RealActualWidth.connect_from(window.RealActualWidth)
        splitscreen_handling.RealActualHeight.connect_from(window.RealActualHeight)
        splitscreen_handling.ScreenTransformIn.value = screen_transform
        self.keep_alive(splitscreen_handling)

        camera, view = self.make_camera(display_view, eye_offset, window, False, num)
        camera.ScreenTransform.connect_from(splitscreen_handling.ScreenTransformOut)
        camera.Viewport.connect_from(splitscreen_handling.ViewportOut)
        return camera, view
    
    
    def make_camera(self, display_view, eye_offset, window, connect_viewport, num):
        camera = avango.osg.viewer.nodes.Camera()
        camera.EyeOffset.value = eye_offset
        if connect_viewport:
            camera.Viewport.connect_from(display_view.Viewport)
        camera.Near.connect_from(display_view.Near)
        camera.Far.connect_from(display_view.Far)
        camera.BackgroundColor.connect_from(display_view.BackgroundColor)
        camera.ViewerTransform.connect_from(display_view.Camera)
        camera.Window.value = window

        view = avango.osg.viewer.nodes.View()
        #depending on camera
        if num == 0:
            view.Scene.connect_from(display_view.RootCamera1)
        else:
            view.Scene.connect_from(display_view.RootCamera2)
            
        view.MasterCamera.value = camera
        return camera, view

    def view_created(self, camera, view, subdisplay=""):
        self._views.append(view)
        camera.ViewerTransform.connect_from(self._users[0].ViewerMatrix)
        print "view_created"

    def make_dominant_user_device(self, user, interface, subdisplay):
        pda_sensor = avango.daemon.nodes.DeviceSensor(DeviceService = self.device_service,
                                                      Station = "ve-dtrack-pda2")
        pda_sensor.TransmitterOffset.value = self._perf2osg
        pda_sensor.ReceiverOffset.value = avango.osg.make_trans_mat(0.076, -0.016, 0.025)
        self.keep_alive(pda_sensor)

        device = avango.display.nodes.Device()
        device.Matrix.connect_from(pda_sensor.Matrix)
        return device


    def make_device(self, device, interface):
        #check for wiimote
        if "wiimote" in device:
            pattern = re.compile("wiimote(\d+)$")
            result = pattern.match(device)
            if not result:
                print "Wiimote device <" + device +"> does not exist."
                return None
            wiimote_num = int(result.group(1))
            if wiimote_num < 1 or wiimote_num > 4:
                print "Wiimote device <" + device +"> does not exist. Currently wiimote 1-4 exists."
                return None

            osg2perf = avango.osg.make_rot_mat(math.radians(90), 1, 0, 0)
            perf2osg = avango.osg.make_rot_mat(math.radians(-90), 1, 0, 0)

            wiimote_station_name = device
            wiimote_dtrack_station_name = self._wiimote_config[wiimote_station_name][0]
            wiimote_offset = self._wiimote_config[wiimote_station_name][1]

            wiimote_offset.y -= 0.1
            wiimote_device = avango.display.make_wiimote_device(wiimote_station_name,
                                                                wiimote_dtrack_station_name,
                                                                self._device_service,
                                                                osg2perf * avango.osg.make_trans_mat(wiimote_offset),
                                                                perf2osg)


            if not wiimote_device:
                print "Could not create device <" + str(device) + ">"
                return None

            #activate the LED according to the num (-1, since the numbering of the leds starts with 0) of the wiimote
            led_field = getattr(wiimote_device,"LED"+str(wiimote_num-1))
            led_field.value = True

            return wiimote_device

        elif device == "StatsViewer":
            stats_viewer = StatsViewer()
            stats_viewer.Views.value = self._views
            return stats_viewer
        
        elif device == "MatrixUserMul":
            if interface == "user1":
                return self.user1_matrix_mul
            #elif interface == "user2":
            #    return self.user1_matrix_mul
            return None
        

class ViewUserSelector(avango.script.Script):
    'Activates or deactivates a viewport depending on the selected user'

    UserSelector = avango.SFInt()
    UserMatch = avango.SFInt()

    ViewIn = avango.osg.viewer.SFView()
    ViewOut = avango.osg.viewer.SFView()

    def evaluate(self):
        if self.UserSelector.value != 0 and self.UserSelector.value != self.UserMatch.value:
            self.ViewOut.value = None
            return

        self.ViewOut.value = self.ViewIn.value


class ViewMerger(avango.script.Script):
    'Merge a list of input fields into an output list of views'

    ViewsOut = avango.osg.viewer.MFView()

    def __init__(self):
        self.super(ViewMerger).__init__()
        self._num_inputs = 0

    def evaluate(self):
        result = []
        for i in xrange(0, self._num_inputs):
            value = self.get_input(i).value
            if value:
                result.append(value)
        self.ViewsOut.value = result

    def get_input(self, index):
        if index >= self._num_inputs:
            return None
        return getattr(self, self.get_input_name(index))

    def get_input_name(self, index):
        return 'ViewIn%i' % index

    def add_input(self):
        result = self._num_inputs
        self._num_inputs += 1

        self.add_field(avango.osg.viewer.SFView(), self.get_input_name(result))

        return result


class ViewportConverter(avango.script.Script):
    """Given a (relative) Viewport (i.e. as rectangular section of a window)
    as new Transformation and (camera) Viewport is calculated."""

    ViewportIn = avango.osg.SFVec4()
    ViewportOut = avango.osg.SFVec4()

    RealActualWidth = avango.SFFloat()
    RealActualHeight = avango.SFFloat()

    ScreenTransformIn = avango.osg.SFMatrix()
    ScreenTransformOut = avango.osg.SFMatrix()

    def evaluate(self):
        viewport_in = self.ViewportIn.value
        self.ViewportOut.value = avango.osg.Vec4(viewport_in.x,
                                                 viewport_in.y,
                                                 viewport_in.z - viewport_in.x,
                                                 viewport_in.w - viewport_in.y)

        x_trans = 0.5 * (viewport_in.x + viewport_in.z - 1.) * self.RealActualWidth.value
        y_trans = 0.5 * (viewport_in.y + viewport_in.w - 1.) * self.RealActualHeight.value
        self.ScreenTransformOut.value = avango.osg.make_trans_mat(x_trans, y_trans, 0.) * self.ScreenTransformIn.value

