import 'package:http/http.dart' as http;

const serverUrl = "http://192.168.0.1";

Uri _getUri(String path) {
  return Uri.parse("$serverUrl$path");
}

Future<void> makeGetRequest(String path) async {
  final uri = _getUri(path);
  await http.get(uri).timeout(const Duration(seconds: 1));
}

Future<void> makePostRequest(String path, String body) async {
  final uri = _getUri(path);
  await http.post(uri, body: body).timeout(const Duration(seconds: 1));
}
