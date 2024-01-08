import 'dart:async';

const _debounceDuration = Duration(milliseconds: 100);

class Debouncer {
  Timer? _running;

  call(Function() callback) {
    final running = _running;
    if (running != null) {
      running.cancel();
    }

    _running = Timer(_debounceDuration, callback);
  }
}