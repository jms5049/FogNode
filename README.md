# Fog Node

### 연구 배경

- 귀농을 희망하는 인구 증가
- 2020년 네트워크에 연결된 IoT 장치가 500억개
- 다량의 데이터로 인한 트래픽 폭증, 서버 부하증가 부작용
- Fog Node를 통해 서버의 역할 대행 필요

### 연구 목표

- IoT 장치의 데이터를 저장, 관리하고 원격 요청에 대응
- 비정상 데이터에 대한 능동적 대처 및 서버로의 보고
- 사용자가 IoT 장치의 상태를 모니터링하고 관리하도록 지원 하는 Fog Node 프로토타입 개발

### Fog Node 란?

![default](https://user-images.githubusercontent.com/26538414/46549724-ee9fad80-c90d-11e8-9d62-0d1b2215ef5e.JPG)

- 다량의 Sensor 데이터가 직접 Server로 전송된다면 트래픽 폭증, 과부하 문제가 발생함
- 위의 문제점을 해결하기 위해 IoT Sensor와 Server 사이에 Fog Node를 두어 모든 데이터들을 저장, 관리하도록 함
- 서버보다 신속하게 IoT 장치 자동 원격 제어가 가능함

### 기본 구조

![default](https://user-images.githubusercontent.com/26538414/46549844-4b9b6380-c90e-11e8-81f4-f4e71788697c.JPG)

- 그림 참조

### 시나리오

1. 지능적 자동제어

![1](https://user-images.githubusercontent.com/26538414/46549847-4c33fa00-c90e-11e8-884f-696492d5f58f.JPG)

- 온도 변화 시 Fog Node가 능동적으로 냉난방장치 가동

2. 비정상 데이터 알림

![2](https://user-images.githubusercontent.com/26538414/46549848-4d652700-c90e-11e8-90ef-bd0d82e35be4.JPG)

- 정상 범위 초과 시 Fog Node가 사용자에게 긴급 알림 발생

3. 데이터 제공 및 시각화

![3](https://user-images.githubusercontent.com/26538414/46549851-4e965400-c90e-11e8-9a37-3789551f9eba.JPG)

- 원하는 센서의 데이터를 요청할 경우 정보 제공 및 시각화

### 기대효과

- 모든 데이터를 Fog Node에서 처리하기 때문에 Server에서의 부하 증가, 트래픽 폭증 문제 해결 가능
- 비정상 데이터 감지 시 Fog Node의 능동적 대응으로 효율성 증가 
- 농작물 종류마다 솔루션이 제시되어 전문적인 지식이 없어도 농작을 시작할 수 있음
- 농부를 대신해 지능적 영농 관리 서비스 제공