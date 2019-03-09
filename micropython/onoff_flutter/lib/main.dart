import 'package:flutter/material.dart';
import 'package:percent_indicator/percent_indicator.dart';
import 'dart:async';
import 'package:http/http.dart' as http;

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "μPython on/off",
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'μPython on/off'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  double _minutes = 60;
  double _seconds = 60;

  void _onOff() async {
    try {
      await http.get("http://10.0.1.60:8000/onoff");
    } catch (e) {}
    ;
  }

  void _decrementTimer() {
    setState(() {
      _seconds -= 1;
      if (_seconds == 0) {
        _seconds = 60;
        _minutes -= 1;
      }
    });
  }

  void _fromSlider(double v) {
    setState(() {   
      _minutes = (v ~/ 5) * 5.0;
      _seconds = 60;
      _timer?.cancel();
    });
  }

  Timer _timer;
  void _startTimer() async {
    _timer?.cancel();
    const oneSec = const Duration(seconds: 1);
    _timer = new Timer.periodic(
        oneSec,
        (Timer timer) => setState(() {
              if (_minutes < 1) {
                timer.cancel();
              } else {
                _decrementTimer();
              }
            }));
    try {
      await http
          .get("http://10.0.1.60:8000/sleep=" + _minutes.toInt().toString());
    } catch (e) {}
    ;
  }

  void _check_delta(d) {
    setState(() {
      _timer?.cancel();
      if (d.delta.dy > 1.5 || d.delta.dx < -1.5) _minutes -= 5;
      if (d.delta.dy < -1.5 || d.delta.dx > 1.5) _minutes += 5;
      if (_minutes < 0) _minutes = 0;
      if (_minutes > 180) _minutes = 180;    
      _minutes = (_minutes ~/ 5) * 5.0;  
      _seconds = 60;
    });
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
        onPanUpdate: _check_delta,
        child: Scaffold(
          appBar: AppBar(
            title: Text(widget.title),
          ),
          body: Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Stack(
                  alignment: AlignmentDirectional.center,
                  children: <Widget>[
                    CircularPercentIndicator(
                      radius: 120,
                      lineWidth: 13,
                      animation: true,
                      percent: _minutes / 180.0,
                      progressColor: Colors.pink[300],
                      backgroundColor: Colors.lightBlue[500],
                    ),
                    CircularPercentIndicator(
                      radius: 150,
                      lineWidth: 13,
                      animation: true,
                      percent: _seconds / 60,
                      progressColor: Colors.grey[500],
                      backgroundColor: Colors.yellow[500],
                    ),
                    FloatingActionButton(
                      backgroundColor: Colors.lightGreen[400],
                    ),
                    Text(
                      _minutes.toInt().toString(),
                      style: TextStyle(fontSize: 16, color: Colors.white),
                    ),
                  ],
                ),
                Padding(padding: EdgeInsets.all(10)),
                Slider(
                  value: _minutes,
                  min: 0,
                  max: 180.0,
                  onChanged: _fromSlider,
                ),
                Padding(padding: EdgeInsets.all(30)),
              ],
            ),
          ),
          floatingActionButton: Row(
            mainAxisAlignment: MainAxisAlignment.end,
            children: <Widget>[
              FloatingActionButton(
                onPressed: _startTimer,
                tooltip: 'Timer',
                child: Icon(Icons.timer),
              ),
              Padding(
                padding: EdgeInsets.all(15),
              ),
              FloatingActionButton(
                onPressed: _onOff,
                tooltip: 'On/Off',
                child: Icon(Icons.power_settings_new),
                backgroundColor: Colors.red,
              ),
            ],
          ),
        ));
  }
}
