#include <windows.h>
//WndProc : �޼����� �ü���� �̸� ���� ���� ���ش�. �Լ������� return
//(�ڵ�, ???, �ΰ�����, �ΰ�����)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	

ATOM MyRegisterClass(HINSTANCE hinstance);

//�����ڵ� WinMain
//wWinMain(
//	_In_ HINSTANCE hInstance,			//���α׷��� �ν��Ͻ� �ڵ�
//	_In_opt_ HINSTANCE hPrevInstance,	//�ٷ� �տ� ����� ���� ���α׷��� �ν��Ͻ� �ڵ�
//	_In_ LPWSTR lpCmdLine,				//��������� �Էµ� ���α׷� �μ�. ������ argv�� �ش�
//	_In_ int nShowCmd					//���α׷��� ����� ����. �ּ�ȭ, ������ ��
//)

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	//1. ������ �������� ���
	MyRegisterClass(hInstance);

	//2. ������ ����
	/*CreateWindow(lpClassName,		//������� �ϴ� �������� Ŭ����( lpszClassName ����� �̸�)
	lpWindowName,					//Ÿ��Ʋ�ٿ� ��Ÿ�� �������� ����
	dwStyle,						//�������� �Ӽ���
	x, y, nWidth, nHeight,
	hWndParent,						//�θ������� ��Ī
	hMenu,						//�����쿡�� ����� �Ŵ��� �ڵ�
	hInstance,					//�ν��Ͻ��� �ڵ�
	lpParam)*/					//MDI���� ����ϴ� ����ü

	HWND hWnd = CreateWindow(				//������Ŭ���� �⺻���� ������ ���� ����
	L"KGCA",
	L"siyeon's window",
	WS_OVERLAPPEDWINDOW, 
	0,0,800,600,NULL, NULL, hInstance,
	NULL);
	//�������� ��� ���� �޸𸮿� ���� �� ������ �ڵ��� ���ϰ����� �Ѱ��ش�. 
	//�Ѱ��� ������ �ڵ��� hWnd ���������� ����Ǿ��ٰ� ������ �����ϴ� ��� �Լ��� �μ��� ���ȴ�.


	if (!hWnd) return 0;
	ShowWindow(hWnd, nShowCmd);		//�޸𸮿� ������� ������ ȭ��� ���

	MSG msg;
	//typedef struct tagMSG {
	//	HWND        hwnd;		//�޼����� ���� ������ �ڵ�
	//	UINT        message;	// � ������ �޼����ΰ�. ���� �߿�
	//	WPARAM      wParam;	// �ΰ����� ����
	//	LPARAM      lParam;	// �ΰ����� ����
	//	DWORD       time;	//�߻� �ð�
	//	POINT       pt;		//���콺 ��ġ
	//}


	//WM_QUIT  -> false

	while (GetMessage(&msg, nullptr, 0, 0))		//�ý����� �����ϴ� �޼���ť���� �޼��� �о� MSG���� ����ü�� ����
												//WM_QUIT�ϰ�� false ������ true
	{
		TranslateMessage(&msg); // �޼��� ����
		DispatchMessage(&msg);	// �޼��� ���ν��� ����		���α׷��� �޼��� ó�� �Լ� WndProc�� ����
	}
	//MessageBox(NULL, L"���������", L"Ÿ��Ʋ", MB_YESNOCANCEL);
	return 1;
	return 1;
}
//ATOM : unsigned short

//MyRegisterClass  �뵵 : âŬ������ ����մϴ�.
//� ������ ���� �Ӽ� -> �ü������ ������ �������� ��� -> ������ ����
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	//UINT        style;	//style : ������ ��Ÿ�� ����. �������� ����, ���� ũ�Ⱑ ���� ��� �ٽ� �׸���.
	//WNDPROC     lpfnWndProc; �޼���ó���Լ�
	//int         cbClsExtra;
	//int         cbWndExtra;
	//HINSTANCE   hInstance;
	//HICON       hIcon;
	//HCURSOR     hCursor;
	//HBRUSH      hbrBackground;
	//LPCWSTR     lpszMenuName;
	//LPCWSTR     lpszClassName; Ŭ��������

	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"KGCA";
	wcex.hInstance = hInstance;					//�� Ŭ������ ����ϴ� ���α׷��� ��ȣ. WinMain�� �μ��� ���޵� hInstance�� �״�� ����
	
	wcex.cbSize = sizeof(WNDCLASSEXW);				//WNDCLASSEX ����ü�� ũ��(����Ʈ����) �Է�
	
	wcex.style = CS_HREDRAW | CS_VREDRAW;			//style : ������ ��Ÿ�� ����. �������� ����, ���� ũ�Ⱑ ���� ��� �ٽ� �׸���.
	wcex.cbClsExtra = 0;							//���࿵��(Ŭ������ �߰����� �޸�)
	wcex.cbWndExtra = 0;
	wcex.hIcon = NULL;									// �ּ�ȭ �� ��� ��µ� ������
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//NULL; 									//���콺 Ŀ�� ���
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1) ;									//������
	wcex.lpszMenuName = NULL;     // 	MAKEINTRESOURCEW(IDC_DEMOWINDOW);							//����� �޴� ����. ���ҽ� �����Ϳ� ���� ������ ��������� ��ũ�� ��������.
	
	return RegisterClassExW(&wcex);			//������Ŭ������ ������ ��Register �Լ� ȣ���� ������ Ŭ���� ���
}        
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);// WM_QUIT �޼���ť ���
		} break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);		//���� �� �������޼��� DefWindowProc�� �ñ��.
															//�ý���ĸ��, �ּ� �ִ� �������̵� ũ�� ���� ���
}