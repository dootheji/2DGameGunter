#include <windows.h>
//WndProc : 메세지를 운영체제가 이를 통해 전달 해준다. 함수포인터 return
//(핸들, ???, 부가정보, 부가정보)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	

ATOM MyRegisterClass(HINSTANCE hinstance);

//유니코드 WinMain
//wWinMain(
//	_In_ HINSTANCE hInstance,			//프로그램의 인스턴스 핸들
//	_In_opt_ HINSTANCE hPrevInstance,	//바로 앞에 실행된 현재 프로그램의 인스턴스 핸들
//	_In_ LPWSTR lpCmdLine,				//명령행으로 입력된 프로그램 인수. 도스의 argv에 해당
//	_In_ int nShowCmd					//프로그램이 실행될 형태. 최소화, 보통모양 등
//)

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	//1. 윈도우 레지스터 등록
	MyRegisterClass(hInstance);

	//2. 윈도우 생성
	/*CreateWindow(lpClassName,		//만들고자 하는 윈도우의 클래스( lpszClassName 멤버의 이름)
	lpWindowName,					//타이틀바에 나타날 윈도우의 제목
	dwStyle,						//윈도우의 속성값
	x, y, nWidth, nHeight,
	hWndParent,						//부모윈도우 지칭
	hMenu,						//윈도우에서 사용할 매뉴의 핸들
	hInstance,					//인스턴스의 핸들
	lpParam)*/					//MDI에서 사용하는 구조체

	HWND hWnd = CreateWindow(				//윈도우클래스 기본으로 윈도우 실제 생성
	L"KGCA",
	L"siyeon's window",
	WS_OVERLAPPEDWINDOW, 
	0,0,800,600,NULL, NULL, hInstance,
	NULL);
	//윈도우의 모든 정보 메모리에 만든 후 윈도우 핸들을 리턴값으로 넘겨준다. 
	//넘겨준 윈도우 핸드은 hWnd 지역변수에 저장되었다가 윈도우 참조하는 모든 함수의 인수로 사용된다.


	if (!hWnd) return 0;
	ShowWindow(hWnd, nShowCmd);		//메모리에 만들어준 윈도우 화면상에 출력

	MSG msg;
	//typedef struct tagMSG {
	//	HWND        hwnd;		//메세지를 받을 윈도우 핸들
	//	UINT        message;	// 어떤 종류의 메세지인가. 가장 중요
	//	WPARAM      wParam;	// 부가적인 정보
	//	LPARAM      lParam;	// 부가적인 정보
	//	DWORD       time;	//발생 시간
	//	POINT       pt;		//마우스 위치
	//}


	//WM_QUIT  -> false

	while (GetMessage(&msg, nullptr, 0, 0))		//시스템이 유지하는 메세지큐에서 메세지 읽어 MSG형의 구조체에 대입
												//WM_QUIT일경우 false 나머지 true
	{
		TranslateMessage(&msg); // 메세지 번역
		DispatchMessage(&msg);	// 메세지 프로시져 전달		프로그램의 메세지 처리 함수 WndProc로 전달
	}
	//MessageBox(NULL, L"윈도우생성", L"타이틀", MB_YESNOCANCEL);
	return 1;
	return 1;
}
//ATOM : unsigned short

//MyRegisterClass  용도 : 창클래스를 등록합니다.
//어떤 윈도우 생성 속성 -> 운영체제에게 윈도우 레지스터 등록 -> 윈도우 생성
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	//UINT        style;	//style : 윈도우 스타일 지정. 윈도우의 수직, 수평 크기가 변할 경우 다시 그린다.
	//WNDPROC     lpfnWndProc; 메세지처리함수
	//int         cbClsExtra;
	//int         cbWndExtra;
	//HINSTANCE   hInstance;
	//HICON       hIcon;
	//HCURSOR     hCursor;
	//HBRUSH      hbrBackground;
	//LPCWSTR     lpszMenuName;
	//LPCWSTR     lpszClassName; 클래스네임

	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"KGCA";
	wcex.hInstance = hInstance;					//이 클래스를 사용하는 프로그램의 번호. WinMain의 인수로 전달된 hInstance값 그대로 대입
	
	wcex.cbSize = sizeof(WNDCLASSEXW);				//WNDCLASSEX 구조체의 크기(바이트단위) 입력
	
	wcex.style = CS_HREDRAW | CS_VREDRAW;			//style : 윈도우 스타일 지정. 윈도우의 수직, 수평 크기가 변할 경우 다시 그린다.
	wcex.cbClsExtra = 0;							//예약영역(클래스의 추가적인 메모리)
	wcex.cbWndExtra = 0;
	wcex.hIcon = NULL;									// 최소화 될 경우 출력될 아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//NULL; 									//마우스 커서 모양
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1) ;									//배경색상
	wcex.lpszMenuName = NULL;     // 	MAKEINTRESOURCEW(IDC_DEMOWINDOW);							//사용할 메뉴 지정. 리소스 에디터에 의해 별도로 만들어지며 링크시 합쳐진다.
	
	return RegisterClassExW(&wcex);			//윈도우클래스를 정의한 후Register 함수 호출해 윈도우 클래스 등록
}        
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);// WM_QUIT 메세지큐 등록
		} break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);		//종료 외 나머지메세지 DefWindowProc에 맡긴다.
															//시스템캡션, 최소 최대 윈도우이동 크기 변경 등등
}