# RaspberryController 프로젝트
- - -
## 프로젝트 간략 소개
> 라즈베리파이를 사용하여 조이스틱과 버튼을 입력 받고 Unity로 만든 Windows 게임과 통신하는 프로젝트 <br />
> 개발 언어: C++ < br />
> 환경: Raspberry Pi 4 Model B Rev 1.2 / Raspbian GNU/Linux 10 (buster) <br />

- - - 

## 1. 요구사항 분석
1. 요구사항
> 요구사항 식별자: R_[Number]

| Requirements ID | Description |
| --- | --- |
| R_1 | 조이스틱 2개(움직임, 조준) 입력 처리 |
| R_2 | 버튼 7개(스킬, 무기, 패링, UI 조작 등) 입력 처리 |
| R_3 | 입력된 것 통신 처리 |

2. 요구사항 분석
> 요구사항 분석 항목 식별자: [Requirements ID].RA_[Number]

| Requirements Analysis ID | Description |
| --- | --- |
| R_1.RA_1 | 조이스틱의 움직임을 정확하게 측정하고 입력 받아야 한다. |
| R_1.RA_2 | 조이스틱의 움직임을 각도 값으로 변환해야 한다. |
| R_1.RA_3 | 왼쪽 조이스틱은 움직임을 입력 받는 값이며, 오른쪽 조이스틱은 조준 기능을 입력 받는다. |
| R_1.RA_4 | 버튼 눌림 값도 처리해야 한다. |
| R_2.RA_1 | 눌린 버튼 번호와 눌림 여부를 처리해야 한다. |
| R_3.RA_1 | 입력된 값을 전송해야 한다. |

- - - 

## 2. 시스템 설계
> 시스템 설계 항목 식별자: SD_[Number]

| System Design ID | Description | Requirements Analysis ID |
| --- | --- | --- |
| SD_1 | MCP 3008 ADC를 이용하여 SPI 통신을 통해 해당 조이스틱의 아날로그 출력을 디지털로 변환하여 입력 받는다. | R_1.RA_1 |
| SD_2 | 입력 받은 X, Y 값을 위쪽이 0도가 되고 시계방향으로 각도가 증가하여 360도로 끝나는 값으로 변환한다. | R_1.RA_2 |
| SD_3 | 왼쪽 조이스틱의 경우 움직임을 입력 받는 값이기 때문에 왼쪽 오른쪽의 방향 값만 담아 작업큐에 넣는다. 오른쪽 조이스틱의 경우 조준 기능이기 때문에 그냥 각도 값을 그대로 넣는다. 작업큐에 넣을 때는 이전의 값과 동일한 경우 넣지 않는다. | R_1.RA_3 |
| SD_4 | 버튼 눌림 값도 따로 처리한다. 누르기 시작했을 때 한번, 땠을 때 한번 작업큐에 넣는다. | R_1.RA_4 |
| SD_5 | 눌린 버튼 번호와 눌림 여부를 작업큐에 넣는다. 이때 위와 동일하게 누르기 시작했을 때 한번, 땠을 때 한번 작업큐에 넣는다. | R_2.RA_1 |
| SD_6 | 작업큐에 들어온 객체들의 필드를 하나씩 bit로 변경하여 패킷 번호, 패킷 사이즈와 함께 전송한다. 패킷의 처리 방식 역시 정의한다. | R_3.RA_1 |

- - -

## 3. 아키텍처 설계
> 아키텍처 설계 항목 식별자: SAD_[Number]

| Software Architecture Design ID | SAD_1 |
| --- | --- |
| Description | 조이스틱과 버튼에서 입력을 받아 처리한다. MCP 3008 ADC와 SPI 통신을 통해 아날로그 입력을 디지털 입력으로 변환해서 받는다. |
| Related Functions | 조이스틱 및 버튼 입력 처리 |
| System Design IDs | SD_1, SD_2, SD_3, SD_4, SD_5 |

| Software Architecture Design ID | SAD_2 |
| --- | --- |
| Description | 작업 큐를 이용하여 가공된 입력을 패킷으로 가공해 넣는다. |
| Related Functions | 패킷 생성 |
| System Design IDs | SD_6 |

| Software Architecture Design ID | SAD_3 |
| --- | --- |
| Description | 작업 큐의 패킷을 연결된 블루투스를 통해 내보낸다. |
| Related Functions | 블루투스 통신 |
| System Design IDs | SD_6 |

- - -

