#Updates

#### Fog Node , Server는 AWS를 사용한 Cloud 환경

## Arduino

- 센서 값 읽어오기
- Fog Node와 통신하기

## Arduino <-> Fog Node [Cloud]

- MQTT 통신
- Opensource (Mosquitto)

## Fog Node [Cloud]

- Arduino로부터 센서 값 가져오기
- Database 생성 및 저장하기
- Opensource (InfluxDB for Database)

## Fog Node [Cloud] <-> Server [Cloud]

- DDS 통신
- 개발중

## Server [Cloud]

- 사용자 UI 구축
- 사용자로부터 값 읽어오기
- 사용자 모바일에 알람주기
- Opensource (Grafana for Visualization)

## Server [Cloud] <-> User

- 웹
- AWS 사용

