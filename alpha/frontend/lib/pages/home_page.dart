import 'package:flutter/material.dart';
import 'package:frontend/components/led_control.dart';
import 'package:frontend/components/servo_control.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  bool led1 = false;
  bool led2 = false;

  @override
  Widget build(BuildContext context) {
    final scheme = Theme.of(context).colorScheme;

    return Scaffold(
      appBar: AppBar(
        title: const Text("xRobotics"),
        backgroundColor: scheme.primaryContainer,
      ),
      body: const Column(
        children: [
          LedControl(
            label: "LED Nr 1 (gelb)",
            endpoint: "/led1",
          ),
          LedControl(
            label: "LED Nr 2 (blau)",
            endpoint: "/led2",
          ),
          Divider(),
          ServoControl(
            label: "Servo Control",
          ),
        ],
      ),
    );
  }
}
