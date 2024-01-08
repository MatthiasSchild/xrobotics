import 'package:flutter/material.dart';
import 'package:frontend/api/api.dart';
import 'package:frontend/components/slider_component.dart';
import 'package:frontend/utils/debouncer.dart';

class ServoControl extends StatefulWidget {
  final String label;

  const ServoControl({
    super.key,
    required this.label,
  });

  @override
  State<ServoControl> createState() => _ServoControlState();
}

class _ServoControlState extends State<ServoControl> {
  final debouncer = Debouncer();
  double value = 0.0;

  void _showError(BuildContext context, Object e) {
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(content: Text(e.toString())),
    );
  }

  void _triggerSend(BuildContext context, double value) async {
    final degree = (value * 180).floor().toString();

    try {
      await makePostRequest("/servo", degree);
    } catch (e) {
      if (context.mounted) {
        _showError(context, e);
      }
    }
  }

  void _onValueChange(BuildContext context, double value) async {
    setState(() {
      this.value = value;
    });

    debouncer.call(() => _triggerSend(context, value));
  }

  @override
  Widget build(BuildContext context) {
    return SliderComponent(
      label: widget.label,
      value: value,
      onChanged: (value) => _onValueChange(context, value),
    );
  }
}
