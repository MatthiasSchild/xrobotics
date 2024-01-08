import 'package:flutter/material.dart';

class SwitchControl extends StatelessWidget {
  final String label;
  final bool value;
  final bool loading;
  final Function(bool) onChanged;

  const SwitchControl({
    super.key,
    required this.label,
    required this.value,
    required this.loading,
    required this.onChanged,
  });

  @override
  Widget build(BuildContext context) {
    Widget trailing = Switch(
      value: value,
      onChanged: onChanged,
    );

    if (loading) {
      trailing = const CircularProgressIndicator();
    }

    return ListTile(
      title: Text(label),
      trailing: trailing,
    );
  }
}
