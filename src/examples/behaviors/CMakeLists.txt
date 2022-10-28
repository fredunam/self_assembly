if(ARGOS_BUILD_FOR_SIMULATOR)
  include_directories(${CMAKE_SOURCE_DIR}/plugins/robots/kilobot/control_interface)

  #
  # Lab0: Blinky
  #
  add_executable(blinky blinky.c)
  target_link_libraries(blinky argos3plugin_simulator_kilolib)

  #
  # Lab1.2: Simple Movement
  #
  add_executable(simple_movement simple_movement.c)
  target_link_libraries(simple_movement argos3plugin_simulator_kilolib)

  #
  # Lab1.3: Non-blocked Movement
  #
  add_executable(nonblocked_movement nonblocked_movement.c)
  target_link_libraries(nonblocked_movement argos3plugin_simulator_kilolib)

  #
  # Lab2.1-2.2: Test Speaker and Test Listener
  #
  add_executable(test_speaker test_speaker.c)
  target_link_libraries(test_speaker argos3plugin_simulator_kilolib)
  add_executable(test_listener test_listener.c)
  target_link_libraries(test_listener argos3plugin_simulator_kilolib)

  #
  # Lab2.3-2.4: Modified Test Speaker and Test Listener
  #
  add_executable(test_speaker_mod test_speaker_mod.c)
  target_link_libraries(test_speaker_mod argos3plugin_simulator_kilolib)
  add_executable(test_listener_mod test_listener_mod.c)
  target_link_libraries(test_listener_mod argos3plugin_simulator_kilolib)

  #
  # Lab3: Disperse
  #
  add_executable(disperse disperse.c)
  target_link_libraries(disperse argos3plugin_simulator_kilolib)

  #
  # Lab4: Orbit
  #
  add_executable(orbit_star orbit_star.c)
  target_link_libraries(orbit_star argos3plugin_simulator_kilolib)
  add_executable(orbit_planet orbit_planet.c)
  target_link_libraries(orbit_planet argos3plugin_simulator_kilolib)

  #
  # Lab5: Move to Light
  #
  add_executable(move_to_light move_to_light.c)
  target_link_libraries(move_to_light argos3plugin_simulator_kilolib)

  #
  # Lab6: Simple Gradient
  #
  add_executable(gradient_simple gradient_simple.c)
  target_link_libraries(gradient_simple argos3plugin_simulator_kilolib)

  #
  # Lab7: Sync
  #
  add_executable(sync sync.c)
  target_link_libraries(sync argos3plugin_simulator_kilolib)

  #
  # Debugging example
  #
  add_executable(test_debug test_debug.h test_debug.c)
  target_link_libraries(test_debug argos3plugin_simulator_kilolib)

  #
  # Lab ark
  #
  add_executable(lab_foraging lab_foraging.c)
  target_link_libraries(lab_foraging argos3plugin_simulator_kilolib)


  #
  # shape_formation
  #
  add_executable(shape_formation shape_formation.c)
  target_link_libraries(shape_formation argos3plugin_simulator_kilolib)

  #
  # orbit_FSM
  #
  add_executable(orbit_FSM orbit_FSM.c)
  target_link_libraries(orbit_FSM argos3plugin_simulator_kilolib)

  #
  # orbit_original
  #
  add_executable(orbit_original orbit_original.c)
  target_link_libraries(orbit_original argos3plugin_simulator_kilolib)

  #
  # orbit2
  #
  add_executable(orbit2 orbit2.c)
  target_link_libraries(orbit2 argos3plugin_simulator_kilolib)

  #
  # preuve_desaxe
  #
  add_executable(preuve_desaxe preuve_desaxe.c)
  target_link_libraries(preuve_desaxe argos3plugin_simulator_kilolib)

  #
  # rectangle
  #
  add_executable(rectangle rectangle.c)
  target_link_libraries(rectangle argos3plugin_simulator_kilolib)
  add_executable(rectangle_star rectangle_star.c)
  target_link_libraries(rectangle_star argos3plugin_simulator_kilolib)

  #
  # triangle
  #
  add_executable(triangle triangle.c)
  target_link_libraries(triangle argos3plugin_simulator_kilolib)
  add_executable(triangle_star triangle_star.c)
  target_link_libraries(triangle_star argos3plugin_simulator_kilolib)

endif(ARGOS_BUILD_FOR_SIMULATOR)
