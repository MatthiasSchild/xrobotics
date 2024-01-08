import 'package:flutter/material.dart';

import '../api/api.dart';
import 'switch_control.dart';

class LedControl extends StatefulWidget {
  final String label;
  final String endpoint;

  const LedControl({
    super.key,
    required this.label,
    required this.endpoint,
  });

  @override
  State<LedControl> createState() => _LedControlState();
}

class _LedControlState extends State<LedControl> {
  bool state = false;
  bool loading = false;

  void _showError(BuildContext context, Object e) {
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(content: Text(e.toString())),
    );
  }

  void _onToggle(BuildContext context, bool value) async {
    setState(() {
      loading = true;
    });

    try {
      final append = value ? '/on' : '/off';
      await makeGetRequest(widget.endpoint + append);

      setState(() => state = value);
    } catch (e) {
      if (context.mounted) {
        _showError(context, e);
      }
    } finally {
      setState(() => loading = false);
    }
  }

  @override
  Widget build(BuildContext context) {
    return SwitchControl(
      label: widget.label,
      value: state,
      loading: loading,
      onChanged: (value) => _onToggle(context, value),
    );
  }
}
