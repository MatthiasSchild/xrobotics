import 'package:flutter/material.dart';

class SliderComponent extends StatelessWidget {
  final String label;
  final double value;
  final Function(double) onChanged;

  const SliderComponent({
    super.key,
    required this.label,
    required this.value,
    required this.onChanged,
  });

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisSize: MainAxisSize.min,
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Padding(
          padding: const EdgeInsets.symmetric(horizontal: 16),
          child: Text(
            label,
            style: const TextStyle(
              fontSize: 16,
            ),
          ),
        ),
        Slider(
          value: value,
          onChanged: onChanged,
        ),
      ],
    );
  }
}
