add_library(Shape_loop_function MODULE
        shape.h
        shape.cpp)

target_link_libraries(Shape_loop_function
        argos3core_simulator
        argos3plugin_simulator_dynamics2d
        argos3plugin_simulator_entities
        argos3plugin_simulator_media
        argos3plugin_simulator_kilobot
        argos3plugin_simulator_kilolib
        ${ARGOS_QTOPENGL_LIBRARIES})