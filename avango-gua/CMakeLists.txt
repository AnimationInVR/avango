###############################################################################
# determine source and header files
###############################################################################
file(GLOB_RECURSE AVANGO_GUA_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/avango/gua/*.cpp
    include/avango/gua/*.hpp
)

IF (NOT ${AVANGO_DISTRIBUTION_SUPPORT})
list (REMOVE_ITEM  AVANGO_GUA_SRC
    src/avango/gua/network/Init.cpp
    src/avango/gua/network/NetTransform.cpp
    src/avango/gua/network/SharedContainerHolder.cpp
    include/avango/gua/network/FragmentGroup.h
    include/avango/gua/network/Init.h
    include/avango/gua/network/NetTransform.h
    include/avango/gua/network/SharedContainerHolder.h
)
ENDIF (NOT ${AVANGO_DISTRIBUTION_SUPPORT})

IF (NOT ${AVANGO_PBR_SUPPORT})
list (REMOVE_ITEM  AVANGO_GUA_SRC
    src/avango/gua/scenegraph/PLODNode.cpp
    src/avango/gua/scenegraph/PBRNode.cpp
    src/avango/gua/renderer/PLODLoader.cpp
    src/avango/gua/renderer/PBRLoader.cpp
    include/avango/gua/scenegraph/PLODNode.h
    include/avango/gua/scenegraph/PBRNode.h
    include/avango/gua/renderer/PLODLoader.h
    include/avango/gua/renderer/PBRLoader.h
)
ENDIF (NOT ${AVANGO_PBR_SUPPORT})

IF (NOT ${AVANGO_PHYSICS_SUPPORT})
list (REMOVE_ITEM  AVANGO_GUA_SRC
  include/avango/gua/physics/BoxShape.hpp
  include/avango/gua/physics/CollisionShape.hpp
  include/avango/gua/physics/CollisionShapeNode.hpp
  include/avango/gua/physics/Constraint.hpp
  include/avango/gua/physics/ConvexHullShape.hpp
  include/avango/gua/physics/CylinderShape.hpp
  include/avango/gua/physics/FixedConstraint.hpp
  include/avango/gua/physics/HingeConstraint.hpp
  include/avango/gua/physics/Physics.hpp
  include/avango/gua/physics/PlaneShape.hpp
  include/avango/gua/physics/Point2PointConstraint.hpp
  include/avango/gua/physics/RigidBodyNode.hpp
  include/avango/gua/physics/SliderConstraint.hpp
  include/avango/gua/physics/SphereShape.hpp
  include/avango/gua/physics/TriangleMeshShape.hpp
  src/avango/gua/physics/BoxShape.cpp
  src/avango/gua/physics/CollisionShape.cpp
  src/avango/gua/physics/CollisionShapeNode.cpp
  src/avango/gua/physics/Constraint.cpp
  src/avango/gua/physics/ConvexHullShape.cpp
  src/avango/gua/physics/CylinderShape.cpp
  src/avango/gua/physics/FixedConstraint.cpp
  src/avango/gua/physics/HingeConstraint.cpp
  src/avango/gua/physics/Physics.cpp
  src/avango/gua/physics/PlaneShape.cpp
  src/avango/gua/physics/Point2PointConstraint.cpp
  src/avango/gua/physics/RigidBodyNode.cpp
  src/avango/gua/physics/SliderConstraint.cpp
  src/avango/gua/physics/SphereShape.cpp
  src/avango/gua/physics/TriangleMeshShape.cpp
  )
ENDIF (NOT ${AVANGO_PHYSICS_SUPPORT})

file(GLOB_RECURSE AVANGO_GUA_PYTHON_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    python/avango/gua/*.c
    python/avango/gua/*.cpp
    python/avango/gua/*.h
    python/avango/gua/*.hpp
)

IF (NOT ${AVANGO_DISTRIBUTION_SUPPORT})
list (REMOVE_ITEM  AVANGO_GUA_PYTHON_SRC
    python/avango/gua/network/NetTransform.h
    python/avango/gua/network/NetTransform.cpp
)
ENDIF (NOT ${AVANGO_DISTRIBUTION_SUPPORT})

IF (NOT ${AVANGO_PBR_SUPPORT})
list (REMOVE_ITEM  AVANGO_GUA_PYTHON_SRC
  python/avango/gua/scenegraph/PLODNode.hpp
  python/avango/gua/scenegraph/PLODNode.cpp
  python/avango/gua/scenegraph/PBRNode.hpp
  python/avango/gua/scenegraph/PBRNode.cpp
  python/avango/gua/renderer/PLODLoader.hpp
  python/avango/gua/renderer/PLODLoader.cpp
  python/avango/gua/renderer/PBRLoader.hpp
  python/avango/gua/renderer/PBRLoader.cpp
)
ENDIF (NOT ${AVANGO_PBR_SUPPORT})

IF (NOT ${AVANGO_PHYSICS_SUPPORT})
list (REMOVE_ITEM  AVANGO_GUA_PYTHON_SRC
  python/avango/gua/physics/BoxShape.cpp
  python/avango/gua/physics/BoxShape.hpp
  python/avango/gua/physics/CollisionShape.cpp
  python/avango/gua/physics/CollisionShape.hpp
  python/avango/gua/physics/CollisionShapeNode.cpp
  python/avango/gua/physics/CollisionShapeNode.hpp
  python/avango/gua/physics/Constraint.cpp
  python/avango/gua/physics/Constraint.hpp
  python/avango/gua/physics/ConvexHullShape.cpp
  python/avango/gua/physics/ConvexHullShape.hpp
  python/avango/gua/physics/CylinderShape.cpp
  python/avango/gua/physics/CylinderShape.hpp
  python/avango/gua/physics/FixedConstraint.cpp
  python/avango/gua/physics/FixedConstraint.hpp
  python/avango/gua/physics/HingeConstraint.cpp
  python/avango/gua/physics/HingeConstraint.hpp
  python/avango/gua/physics/Physics.cpp
  python/avango/gua/physics/PhysicsDatabase.cpp
  python/avango/gua/physics/PhysicsDatabase.hpp
  python/avango/gua/physics/Physics.hpp
  python/avango/gua/physics/PlaneShape.cpp
  python/avango/gua/physics/PlaneShape.hpp
  python/avango/gua/physics/Point2PointConstraint.cpp
  python/avango/gua/physics/Point2PointConstraint.hpp
  python/avango/gua/physics/RigidBodyNode.cpp
  python/avango/gua/physics/RigidBodyNode.hpp
  python/avango/gua/physics/SliderConstraint.cpp
  python/avango/gua/physics/SliderConstraint.hpp
  python/avango/gua/physics/SphereShape.cpp
  python/avango/gua/physics/SphereShape.hpp
  python/avango/gua/physics/TriangleMeshShape.cpp
  python/avango/gua/physics/TriangleMeshShape.hpp
  )
ENDIF (NOT ${AVANGO_PHYSICS_SUPPORT})

###############################################################################
# set link directories
###############################################################################
LINK_DIRECTORIES(${LIB_PATHS}
                 ${PYTHON_LIBRARY_DIRS}
                 ${BOOST_LIBRARY_DIRS}
                 ${SCHISM_LIBRARY_DIRS}
                 ${BULLET_LIBRARY_DIRS}
)


###############################################################################
# create libraries
###############################################################################
INCLUDE_DIRECTORIES(BEFORE
  include
  include/avango/python/
  ${INCLUDE_PATHS}
  ${PYTHON_INCLUDE_DIRS}
  ${SCHISM_INCLUDE_DIRS}
  ${BULLET_INCLUDE_DIRS}
  ${JSON_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/avango-core/include
  ${CMAKE_SOURCE_DIR}/avango-python/include
)

ADD_LIBRARY( avango_gua SHARED
    	     ${AVANGO_GUA_SRC}
)

ADD_LIBRARY( _gua SHARED
    	     ${AVANGO_GUA_PYTHON_SRC}
)

set_target_properties( _gua
  PROPERTIES LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_SOURCE_DIR}/lib/avango/gua
)

ADD_DEPENDENCIES(avango_gua avango)
ADD_DEPENDENCIES(_gua avango avango_gua)

###############################################################################
# set preprocessor configuration
###############################################################################
SET( AVANGO_GUA_BUILD_FLAGS "${BUILD_FLAGS} -D AV_GUA_LIBRARY")
SET( AVANGO_GUA_PYTHON_BUILD_FLAGS "${BUILD_FLAGS} ")

IF (MSVC)
	SET( AVANGO_GUA_BUILD_FLAGS "${AVANGO_GUA_BUILD_FLAGS} /bigobj")
ENDIF (MSVC)

set_target_properties(avango_gua PROPERTIES COMPILE_FLAGS "${AVANGO_GUA_BUILD_FLAGS}")
set_target_properties(avango_gua PROPERTIES COMPILE_DEFINITIONS_DEBUG "_AVANGO_DEBUG=1")

set_target_properties(_gua PROPERTIES COMPILE_FLAGS "${AVANGO_GUA_PYTHON_BUILD_FLAGS}")
set_target_properties(_gua PROPERTIES COMPILE_DEFINITIONS_DEBUG "_AVANGO_DEBUG=1")

###############################################################################
# set dependencies
###############################################################################
SET(_AVANGO_GUA_LIBRARIES ${LIBRARIES}
                          ${PYTHON_LIBRARIES}
                          ${BOOST_LIBRARIES}
                          ${BULLET_LIBRARIES}
                          ${JSON_LIBRARIES}
                          ${ASSIMP_LIBRARIES}
                          ${SCHISM_LIBRARIES}
                          avango
                          avango_gua
)

IF (UNIX)
	LIST(APPEND _AVANGO_GUA_LIBRARIES boost_program_options boost_regex)
ENDIF (UNIX)

TARGET_LINK_LIBRARIES( avango_gua
                       debug
                       ${_AVANGO_GUA_LIBRARIES}
                       optimized
                       ${_AVANGO_GUA_LIBRARIES}
)

TARGET_LINK_LIBRARIES( _gua
                       debug
                       ${_AVANGO_GUA_LIBRARIES}
                       optimized
                       ${_AVANGO_GUA_LIBRARIES}
)

SET_TARGET_PROPERTIES( _gua PROPERTIES PREFIX "")

IF (UNIX)
	SET_TARGET_PROPERTIES( _gua PROPERTIES COMPILE_FLAGS -fPIC)
ENDIF (UNIX)

###############################################################################
# install modules
###############################################################################
IF (MSVC)
  post_build_install_target(avango_gua ${AVANGO_INSTALL_DIRECTORY}/avango/avango_gua.dll)
  post_build_install_target(_gua ${AVANGO_INSTALL_DIRECTORY}/python2.7/avango/gua/_gua.pyd)
ELSEIF (UNIX)
  post_build_install_target(avango_gua ${AVANGO_INSTALL_DIRECTORY}/avango/libavango_gua.so)
  post_build_install_target(_gua ${AVANGO_INSTALL_DIRECTORY}/python2.7/avango/gua/_gua.so)
ENDIF (MSVC)

COPY_PYTHON_FILES_INTO_DIRECTORY(
    ${CMAKE_SOURCE_DIR}/avango-gua/lib/avango/gua
    ${AVANGO_INSTALL_DIRECTORY}/python2.7/avango/gua
    _gua
)

###############################################################################
# targets for unittesting
###############################################################################
IF (AVANGO_UNITTESTS)

ENDIF (AVANGO_UNITTESTS)
