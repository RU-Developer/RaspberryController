# RaspberryController 프로젝트
- - -
## 프로젝트 간략 소개
> 라즈베리파이를 사용하여 조이스틱과 버튼을 입력 받고 Unity로 만든 Windows 게임과 통신하는 프로젝트 <br />
> 개발 언어: C++ <br />
> 환경: Raspberry Pi 4 Model B Rev 1.2 / Raspbian GNU/Linux 10 (buster) <br />

- - - 

## 1. 요구사항 분석
1. 요구사항
> 요구사항 식별자: R_[Number]

| Requirements ID | Description |
| --- | --- |
| R_1 | 조이스틱 2개(움직임, 조준)의 입력을 처리한다. |
| R_2 | 버튼 7개(스킬, 무기, 패링, UI 조작 등)의 입력을 처리한다. |
| R_3 | 입력된 것을 Unity 게임 프로젝트에 전송한다. |

2. 요구사항 분석
> 요구사항 분석 항목 식별자: [Requirements ID].RA_[Number]

| Requirements Analysis ID | Description |
| --- | --- |
| R_1.RA_1 | 조이스틱의 움직임을 정확하게 측정하고 입력 받아야 한다. |
| R_1.RA_2 | 조이스틱의 움직임을 각도 값으로 변환해야 한다. |
| R_1.RA_3 | 왼쪽 조이스틱은 움직임과 조준을 입력 받는 값이며, 오른쪽 조이스틱은 조준 기능을 입력 받는다. 오른쪽 조이스틱으로 조준을 하고 있을 경우 왼쪽 조이스틱은 움직임만 조작해야 한다. |
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
| SD_3 | 왼쪽 조이스틱은 움직임과 조준을 입력 받는 값이며, 오른쪽 조이스틱은 조준 기능을 입력 받는다. 오른쪽 조이스틱으로 조준을 하고 있을 경우 왼쪽 조이스틱은 움직임만 조작한다. | R_1.RA_3 |
| SD_4 | 버튼도 조이스틱과 마찬가지로 눌렀을때, 땠을 때 값을 조작한다. | R_1.RA_4 |
| SD_5 | 전체 키들을 묶어서 하나의 데이터(32bit 정수형)로 만든다. MSB(1bit), 버튼 번호와 눌림 여부(각 버튼당 1bit 총 9bit), 조이스틱의 움직임(2bit), 조준(20bit)으로 32bit가 필요하기에 충분하다. | R_2.RA_1 |
| SD_6 | WiFi를 이용해 동일한 서브넷에 있는 Unity Client와 통신한다. | R_3.RA_1 |

- - -

## 3. 아키텍처 설계
> 아키텍처 설계 항목 식별자: SAD_[Number]

| Software Architecture Design ID | SAD_1 |
| --- | --- |
| Description | 조이스틱과 버튼에서 입력을 받아 처리한다. MCP 3008 ADC와 SPI 통신을 통해 아날로그 입력을 디지털 입력으로 변환해서 받는다. 왼쪽 조이스틱은 움직임과 조준을 모두 입력 받으며, 오른쪽 조이스틱으로 조준 중일 경우 왼쪽 조이스틱은 움직임만 처리한다. 대역폭 이슈가 없기 때문에 싱글스레드로 구현한다. RaceCondition을 고려할 필요가 없다. |
| Related Classes | Module, ModuleManager, JoyStick, Button |
| System Design IDs | SD_1, SD_2, SD_3, SD_4 |

| Software Architecture Design ID | SAD_2 |
| --- | --- |
| Description | 입력들을 하나의 32bit 정수형 변수로 변경한다. 마찬가지로 멀티스레드는 고려할 필요가 없다. 이전의 데이터를 보관하여 현재 데이터와 다르다면 전송한다. |
| Related Classes | PacketGenerator |
| System Design IDs | SD_5 |

| Software Architecture Design ID | SAD_3 |
| --- | --- |
| Description | 이더넷 통신으로 입력된 데이터를 전송한다. |
| Related Classes | WirelessController, WirelessManager, NetworkManager |
| System Design IDs | SD_6 |

- - -

## 4. 모듈 설계
> 모듈 설계 항목 식별자: SMD_ClassName_[Number] <br />
> 함수는 전부 private 접근 제한이 아닌 외부에서 사용하는 함수만 설계

| Software Module Design ID | Function Name | Description | Software Architecture Design ID |
| --- | --- | --- | --- |
| SMD_Module_01 | ModuleType GetModuleType() | 모듈의 타입을 반환한다. 모든 모듈은 생성했을 때 자신의 ModuleType enum을 가지고 있다. | SAD_1 |
| SMD_Module_02 | virtual int GetInputValue() abstract | 현재 사용중인 모든 모듈들은 전부 라즈베리파이에서 입력을 받는 모듈들이다. 이 모듈을 상속하면 꼭 구현해야 하며, 모듈로부터 입력받은 값을 반환한다. | SAD_1 |
| SMD_Module_03 | virtual void Init() abstract | 모듈이 처음 생성될 때 재정의한 초기화 기능을 호출한다. | SAD_1 |
| SMD_ModuleManager_01 | vector<Module*>& GetModules() | 현재 사용중인 모든 모듈을 vector에 넣어 반환한다. | SAD_1 |
| SMD_ModuleManager_02 | void CreateModule(ModuleType type) | 모듈을 생성해서 관리한다. | SAD_1 |
| SMD_JoyStick_01 | virtual int GetInputValue() override | 조이스틱의 버튼 입력 여부를 반환한다. 눌리면 1 안눌리면 0 | SAD_1 |
| SMD_JoyStick_02 | virtual void Init() override | 조이스틱의 GPIO 핀 모드 설정과 SPI 통신 설정을 한다. | SAD_1 |
| SMD_JoyStick_03 | Coordinate GetCoordinate() | 조이스틱이 일정 범위에 속하면 조이스틱을 움직이지 않은 것으로 취급하여 맨 첫 비트를 1로 주고, 0 ~ 1023의 x, y값을 반환한다. | SAD_1 |
| SMD_Button_01 | virtual int GetInputValue() override | 버튼의 눌림 여부를 반환한다. | SAD_1 |
| SMD_Button_02 | virtual void Init() override | GPIO 핀모드를 설정한다. | SAD_1 |
| SMD_PacketGenerator_01 | int32_t Generate() | 모듈 매니저를 통해 모듈을 가져와서 모든 모듈의 입력값을 받아서 32bit 정수형 타입으로 만들어서 반환한다.<br />MSB(1) 움직임(2)(가만히 10 왼쪽 00 오른쪽 01) 조준x좌표(10) 조준y좌표(10) 조이스틱L버튼(1) 조이스틱R버튼(1) 버튼1~7(7) | SAD_2 |
| SMD_WirelessController_01 | void Init() | WirelessManager를 통해 무선통신을 연결하고, 연결이 성공하면 보내기 시작할 수 있다. | SAD_3 |
| SMD_WirelessController_02 | void IfChangedThenWrite() | 보내야 할 패킷이 이전의 패킷과 다르다면 전송한다. | SAD_3 |
| SMD_WirelessManager_01 | virtual void Init() abstract | 네트워크를 연결한다. | SAD_3 |
| SMD_WirelessManager_02 | virtual void Send(int32_t data) abstract | 데이터를 전송한다. | SAD_3 |
| SMD_NetworkManager_01 | virtual void Init() override | 이더넷 UDP로 유니티 클라이언트를 찾아서 TCP 세션을 연결한다. | SAD_3 |
| SMD_NetworkManager_02 | virtual void Send(int32_t data) override | 데이터를 전송한다. | SAD_3 |

### 클래스 다이어그램
> ![RaspberryController_Class_Diagram_3](https://github.com/RU-Developer/RaspberryController/assets/61056453/33f751b2-44f6-446b-8c2c-c3e50b72cb25)

- - -

