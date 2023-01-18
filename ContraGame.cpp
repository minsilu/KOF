// FIGHTGAME.cpp : 定义应用程序的入口点。
//

#include "ContraGame.h"

using namespace std;


#pragma region 全局变量

#define MAX_LOADSTRING			100

// 全局变量: 
HINSTANCE hInst; // 当前窗体实例句柄
WCHAR szTitle[MAX_LOADSTRING]; // 标题栏文本 
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名

HBITMAP bmp_BG;             //背景图资源
HBITMAP bmp_Title;			//标题图像
HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_HelpBG;			//帮助界面
HBITMAP bmp_StopBG;			//暂停界面
HBITMAP bmp_ChooseBG;		//选角界面
HBITMAP bmp_setBG;			//设置界面
HBITMAP bmp_Stage2;         
HBITMAP bmp_Stage3;

HBITMAP bmp_SetButton;		//设置按钮
HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_HelpButton;		//帮助按钮
HBITMAP bmp_BackButton;		//返回按钮
HBITMAP bmp_ContinueButton;	//继续按钮
HBITMAP bmp_FightButton;	//战斗按钮
HBITMAP bmp_StopButton;		//暂停按钮图像资源
HBITMAP bmp_LButton;		//左箭头按钮
HBITMAP bmp_RButton;		//右箭头按钮
HBITMAP bmp_MenuButton;		//菜单按钮
HBITMAP bmp_ResumeButton;	//恢复本关按钮
HBITMAP bmp_StageButton;	//选择场景按钮


HBITMAP bmp_Unit_kula;			//库拉角色图像资源
HBITMAP bmp_Unit_kyokusanagi;	//草稚京角色图像资源
HBITMAP bmp_Unit_yagami;		//八神图像资源
HBITMAP bmp_Unit_clark;			//克拉克角色图像资源
HBITMAP bmp_Icon1_kula;			//库拉头像1
HBITMAP bmp_Icon1_kyokusanagi;	//草稚京头像1
HBITMAP bmp_Icon1_yagami;		//八神头像1
HBITMAP bmp_Icon1_clark;		//克拉克头像1
HBITMAP bmp_Icon2_kula;			//库拉头像2
HBITMAP bmp_Icon2_kyokusanagi;	//草稚京头像2
HBITMAP bmp_Icon2_yagami;		//八神头像2
HBITMAP bmp_Icon2_clark;		//克拉克头像2
HBITMAP bmp_Name_kula;			//库拉姓名框
HBITMAP bmp_Name_kyokusanagi;	//草稚京姓名框
HBITMAP bmp_Name_yagami;		 //八神姓名框
HBITMAP bmp_Name_clark;			//克拉克姓名框

HBITMAP bmp_Win;		//胜利字样
HBITMAP bmp_Lose;		//失败字样
HBITMAP bmp_vs;			//vs字样
HBITMAP bmp_Easy;
HBITMAP bmp_Normal;
HBITMAP bmp_Medium;
HBITMAP bmp_Hard;
HBITMAP bmp_Ai;
HBITMAP bmp_Town;
HBITMAP bmp_Subway;
HBITMAP bmp_Alley;

Stage* currentStage = NULL; //当前场景状态
vector<Hero*> heros;        //英雄
vector<Button*> buttons;	//按钮

int mouseX = 0;             // 鼠标X
int mouseY = 0;			    // 鼠标Y

int heroList[HERO_NUM] = { HERO_KULA, HERO_KYOKUSANAGI, HERO_CLARK, HERO_YAGAMI };
int myHero = HERO_KULA;
int aiHero = HERO_KYOKUSANAGI;
int myCount = 0;         // 我方英雄选择次数
int aiCount = 1;         // 敌方英雄选择次数

int attackInterval = 0;	//Ai攻击间隔
int redAttackInterval = 0;	//红方Ai攻击间隔
int ultimatekInterval = 0; //Ai大招间隔
int defenceInterval = 0;	//Ai防御间隔
int aiType = 0;
int stageType = 0;			//当前关卡

bool mouseDown = false;     // 鼠标按下
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyAttackDown = false;
bool keyDefenseDown = false;
bool keyUtimate1 = false;
bool keyUtimate2 = false;
bool isAiSkill = false;
bool isRedSkill = false;

bool helpOpen = false;		//帮助界面是否打开
bool stopOpen = false;		//暂停界面是否打开
bool setOpen = false;		//设置界面是否打开
bool winOpen = false;
bool loseOpen = false;

const int TOTAL_TYPE = 9;    // 英雄动作所有类型


#pragma endregion


#pragma region Win32程序框架

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//取消警告
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FIGHTGAME, szWindowClass, MAX_LOADSTRING);


	// 注册窗口类
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIGHTGAME));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// 定义窗口类
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); //结构体的大小

	wcex.style = CS_HREDRAW | CS_VREDRAW; //窗口的风格
	wcex.lpfnWndProc = WndProc; //指定窗口函数为WndProc
	wcex.cbClsExtra = 0; //窗口类占用的额外内存,可以存放窗口类的共有数据，默认为0，不重要
	wcex.cbWndExtra = 0; //窗口占用的额外内存，可以选择其中存放的每个窗口所拥有的数据，默认为0，不重要
	wcex.hInstance = hInstance; //应用程序实例句柄，已经由WinMain函数传递过来了
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); //图标句柄，通过LoadIcon获得应用程序资源定义文件中的资源包含的图标

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //鼠标的光标句柄，通过LoadCursor使用系统默认的光标

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 背景画刷句柄，即指窗口背景颜色
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FIGHTGAME); // 菜单的资源名称
	wcex.lpszClassName = szWindowClass; //窗口类的名字，我们创建窗口时是依靠名字来制定窗口类的
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));  //小图标的句柄，指当窗口最小化时，任务栏显示的程序图标

	//注册窗口类
	return RegisterClassExW(&wcex);

}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		// 禁用输入法
		ImmDisableIME(NULL);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

#pragma endregion


#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_BG = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG));
	bmp_Stage2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE2));
	bmp_Stage3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE3));
	bmp_Title = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TITLE));

	bmp_HelpBG = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP_BG));
	bmp_StopBG = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STOP_BG));
	bmp_ChooseBG = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CHOOSE_BG));
	bmp_setBG = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SET_BG));

	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
	bmp_HelpButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP));
	bmp_BackButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BACK));
	bmp_FightButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FIGHT));
	bmp_StopButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STOP));
	bmp_LButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LARROW));
	bmp_RButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RARROW));
	bmp_MenuButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MENU));
	bmp_ResumeButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESUME));
	bmp_ContinueButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CONTINUE));
	bmp_SetButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SET));
	bmp_StageButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE));

	bmp_Unit_kula = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KULA));
	bmp_Icon1_kula = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KULA_ICON1));
	bmp_Icon2_kula = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KULA_ICON2));
	bmp_Name_kula = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KULA_NAME));

	bmp_Unit_kyokusanagi = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KYO));
	bmp_Icon1_kyokusanagi = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KYO_ICON1));
	bmp_Icon2_kyokusanagi = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KYO_ICON2));
	bmp_Name_kyokusanagi = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_KYO_NAME));

	bmp_Unit_yagami = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_YAG));
	bmp_Icon1_yagami = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_YAG_ICON1));
	bmp_Icon2_yagami = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_YAG_ICON2));
	bmp_Name_yagami = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_YAG_NAME));

	bmp_Unit_clark = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CLA));
	bmp_Icon1_clark = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CLA_ICON1));
	bmp_Icon2_clark = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CLA_ICON2));
	bmp_Name_clark = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CLA_NAME));

	bmp_Win = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_WIN));
	bmp_Lose = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LOSE));
	bmp_vs = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_VS));
	bmp_Easy = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_EASY));
	bmp_Normal = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NORMAL));
	bmp_Medium = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MED));
	bmp_Hard = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HARD));
	bmp_Ai = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_AI));
	bmp_Town = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TOWN));
	bmp_Subway = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SUBWAY));
	bmp_Alley = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ALLEY));

	//添加按钮
	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, 555);
	Button* setButton = CreateButton(BUTTON_SET, bmp_SetButton, BUTTON_SET_WIDTH, BUTTON_SET_HEIGHT,
		WINDOW_WIDTH - BUTTON_SET_WIDTH - 30, 30);
	Button* lButton1 = CreateButton(BUTTON_LARROW, bmp_LButton, BUTTON_LARROW_WIDTH, BUTTON_LARROW_HEIGHT,
		700, 247);
	Button* lButton2 = CreateButton(BUTTON_LARROW2, bmp_LButton, BUTTON_LARROW_WIDTH, BUTTON_LARROW_HEIGHT,
		700, 498);
	Button* rButton1 = CreateButton(BUTTON_RARROW, bmp_RButton, BUTTON_RARROW_WIDTH, BUTTON_RARROW_HEIGHT,
		1037, 247);
	Button* rButton2 = CreateButton(BUTTON_RARROW2, bmp_RButton, BUTTON_RARROW_WIDTH, BUTTON_RARROW_HEIGHT,
		1037, 498);
	Button* fightButton = CreateButton(BUTTON_FIGHT, bmp_FightButton, BUTTON_FIGHT_WIDTH, BUTTON_FIGHT_HEIGHT,
		754, 622);
	Button* helpButton = CreateButton(BUTTON_HELP, bmp_HelpButton, BUTTON_HELP_WIDTH, BUTTON_HELP_HEIGHT,
		(WINDOW_WIDTH - BUTTON_HELP_WIDTH) / 2, 315);
	Button* menuButton = CreateButton(BUTTON_MENU, bmp_MenuButton, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT,
		(WINDOW_WIDTH - BUTTON_MENU_WIDTH) / 2, 419);
	Button* resumeButton = CreateButton(BUTTON_RESUME, bmp_ResumeButton, BUTTON_RESUME_WIDTH, BUTTON_RESUME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_RESUME_WIDTH) / 2, 523);
	Button* backButton = CreateButton(BUTTON_BACK, bmp_BackButton, BUTTON_BACK_WIDTH, BUTTON_BACK_HEIGHT,
		30, 30);
	Button* continueButton = CreateButton(BUTTON_CONTINUE, bmp_ContinueButton, BUTTON_CONTINUE_WIDTH, BUTTON_CONTINUE_HEIGHT,
		(WINDOW_WIDTH - BUTTON_CONTINUE_WIDTH) / 2, 608);
	Button* stopButton = CreateButton(BUTTON_STOP, bmp_StopButton, BUTTON_STOP_WIDTH, BUTTON_STOP_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STOP_WIDTH) / 2, 38);
	Button* stageButton = CreateButton(BUTTON_STAGE, bmp_StageButton, BUTTON_STAGE_WIDTH, BUTTON_STAGE_HEIGHT,
		0, 144);
	Button* aiButton = CreateButton(BUTTON_AI, NULL, BUTTON_AI_WIDTH, BUTTON_AI_HEIGHT,
		0, 144 + DEMO_HEIGHT + BUTTON_STAGE_HEIGHT);
	
	buttons.push_back(startButton);
	buttons.push_back(setButton);
	buttons.push_back(lButton1);
	buttons.push_back(lButton2);
	buttons.push_back(rButton1);
	buttons.push_back(rButton2);
	buttons.push_back(fightButton);
	buttons.push_back(helpButton);
	buttons.push_back(menuButton);
	buttons.push_back(resumeButton);
	buttons.push_back(backButton);
	buttons.push_back(continueButton);
	buttons.push_back(stopButton);
	buttons.push_back(stageButton);
	buttons.push_back(aiButton);

	//初始化背景
	bmp_Background = InitBackGround(hWnd, bmp_BG);

	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_A:
		keyLeftDown = true;
		break;
	case VK_D:
		keyRightDown = true;
		break;
	case VK_W:
		keyUpDown = true;
		break;
	case VK_S:
		keyDownDown = true;
		break;
	case VK_J:
		if ((keyLeftDown || keyRightDown) && !keyAttackDown && !keyDefenseDown && !keyUtimate2 && !keyUpDown)
			keyUtimate1 = true;
		else if (!keyUtimate1 && !keyDefenseDown && !keyUtimate2 && !keyUpDown)
			keyAttackDown = true;
		/*if (keyLeftDown || keyRightDown)
			keyUtimate1 = true;
		else
			keyAttackDown = true;*/
		break;
	case VK_K:
		if ((keyLeftDown || keyRightDown) && !keyAttackDown && !keyDefenseDown && !keyUtimate1 && !keyUpDown)
			keyUtimate2 = true;
		else if (!keyUtimate2 && !keyAttackDown && !keyUtimate1 && !keyUpDown)
			keyDefenseDown = true;
		//if (keyLeftDown || keyRightDown)
		//	keyUtimate2 = true;
		//else
		//	keyDefenseDown = true;
		break;

	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
		//keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case VK_A:
		keyLeftDown = false;
		break;
	case VK_D:
		keyRightDown = false;
		break;
	case VK_W:
		//keyUpDown = false;
		break;
	case VK_S:
		keyDownDown = false;
		break;
	case VK_J:
		//keyAttackDown = false;
		break;
	case VK_K:
		//keyDefenseDown = false;
		break;
	case VK_ESCAPE:
		if (STAGE_1 <= currentStage->stageID && currentStage->stageID <= STAGE_3)
			StopUpdate(hWnd);
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	setOpen = false;
	helpOpen = false;
	stopOpen = false;

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				switch (button->buttonID) {
				case BUTTON_STARTGAME:
				{
					InitStage(hWnd, STAGE_CHOOSE);
					break;
				}
				case BUTTON_SET:
				{
					SetUpdate(hWnd);
					break;
				}
				case BUTTON_HELP:
				{
					HelpUpdate(hWnd);
					break;
				}
				case BUTTON_MENU:
				{
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				case BUTTON_CONTINUE:
				{
					if (currentStage->stageID == STAGE_STARTMENU)
					{
						SetUpdate(hWnd);
					}
					if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_3)
					{
						if (winOpen or loseOpen)
						{
							InitStage(hWnd, STAGE_CHOOSE);
							winOpen = false;
							loseOpen = false;
						}
						else
						{
							StopUpdate(hWnd);
						}
					}
					break;
				}
				case BUTTON_STOP:
				{
					if (!winOpen and !loseOpen)
						StopUpdate(hWnd);
					break;
				}
				case BUTTON_RESUME:
				{
					ResumeUpdate(hWnd);
					break;
				}
				case BUTTON_FIGHT:
				{
					if (stageType == 0){
						InitStage(hWnd, STAGE_1);
					}
					else if (stageType == 1){
						InitStage(hWnd, STAGE_2);
					}
					else if (stageType == 2){
						InitStage(hWnd, STAGE_3);
					}
					
					break;
				}
				case BUTTON_LARROW:
				{
					myCount -= 1;
					ChooseUpdate(hWnd);
					break;
				}
				case BUTTON_RARROW:
				{
					myCount += 1;
					ChooseUpdate(hWnd);
					break;
				}
				case BUTTON_LARROW2:
				{
					aiCount -= 1;
					ChooseUpdate(hWnd);
					break;
				}
				case BUTTON_RARROW2:
				{
					aiCount += 1;
					ChooseUpdate(hWnd);
					break;
				}
				case BUTTON_BACK:
				{
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				case BUTTON_STAGE:
				{
					stageType = (stageType + 1) % STAGE_NUM;
					ChooseUpdate(hWnd);
					break;
				}
				case BUTTON_AI:
				{
					aiType = (aiType + 1) % AI_NUM;
					ChooseUpdate(hWnd);
					break;
				}
				default:
					break;

				}
			}
		}
	}

}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	UpdateUnits(hWnd);
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}



#pragma endregion


#pragma region 其它游戏状态处理函数



//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;
	button->visible = false;
	return button;
}

// 添加英雄函数 
Hero* CreateHero(int type, int x, int y, int health, int blue, int team)
{
	Hero* hero = new Hero();
	hero->type = type;
	hero->team = team;
	hero->frame_length = new int[TOTAL_TYPE];
	hero->frame_width = new int[TOTAL_TYPE];
	hero->frame_height = new int[TOTAL_TYPE];
	hero->frame_total_height = new int[TOTAL_TYPE];
	hero->frame_biasx = new int[TOTAL_TYPE];
	hero->frame_biasy = new int[TOTAL_TYPE];
	if (type == HERO_KULA) {
		/* lengths: 每种动作有多少帧【不包含反转帧】
		   widths: 每种动作中的帧宽度
		   heights: 每种动作中的帧高度
		   bias: 各动作之间为切换协调合理做出的适当的左右偏移
		*/
		int lengths[TOTAL_TYPE] = { 54, 10, 11, 7, 18, 13, 43, 28, 7 },
			widths[TOTAL_TYPE] = { 50, 57, 126, 73, 127, 86, 318, 169,71 },
			heights[TOTAL_TYPE] = { 107, 107, 115, 117, 170, 208, 208, 117,107 },
			biasx[TOTAL_TYPE] = { -5, 5, -7, -8, 9, -8, 48, 41, -15 },// bias为经验性调整
			biasy[TOTAL_TYPE] = { 0, 0, -4, -3, -13, -51, -25, -5, 0 };
		hero->img = bmp_Unit_kula;
		for (int j = 0; j < TOTAL_TYPE; j++) {
			hero->frame_length[j] = lengths[j];
			hero->frame_width[j] = widths[j];
			hero->frame_height[j] = heights[j];
			if (j == 0) hero->frame_total_height[j] = 0;
			else hero->frame_total_height[j] = heights[j - 1] + hero->frame_total_height[j - 1];
			hero->frame_biasx[j] = biasx[j];
			hero->frame_biasy[j] = biasy[j];
		}
	}
	else if (type == HERO_KYOKUSANAGI) {
		int lengths[TOTAL_TYPE] = { 10, 6, 4, 14, 12, 13, 19, 6, 4 },
			widths[TOTAL_TYPE] = { 64, 63, 89, 109, 150, 87, 121, 96, 83 },
			heights[TOTAL_TYPE] = { 106, 118, 105, 117, 123, 183, 196, 99, 109 },
			biasx[TOTAL_TYPE] = { 1, 0, 12, 18, 6, -9, 27, 4, -3 },
			biasy[TOTAL_TYPE] = { -1, -7, -1, -7, 9, -40, -46, 3, -3 };
		hero->img = bmp_Unit_kyokusanagi;
		for (int j = 0; j < TOTAL_TYPE; j++) {
			hero->frame_length[j] = lengths[j];
			hero->frame_width[j] = widths[j];
			hero->frame_height[j] = heights[j];
			if (j == 0) hero->frame_total_height[j] = 0;
			else hero->frame_total_height[j] = heights[j - 1] + hero->frame_total_height[j - 1];
			hero->frame_biasx[j] = biasx[j];
			hero->frame_biasy[j] = biasy[j];
		}
	}
	else if (type == HERO_CLARK) {
		int	lengths[TOTAL_TYPE] = { 35, 16, 27, 6, 26, 14, 25, 27, 8 },
			widths[TOTAL_TYPE] = { 84, 81, 161, 82, 166, 85, 172, 175, 80 },
			heights[TOTAL_TYPE] = { 109, 112, 134, 109, 161, 196, 139, 116, 108 },
			biasx[TOTAL_TYPE] = { 5, -2, 32, -6, -40, -7, 49, 42, -8 },
			biasy[TOTAL_TYPE] = { 0, -2, -13, 0, -21, -44, -15, 5, 1 };
		hero->img = bmp_Unit_clark;
		for (int j = 0; j < TOTAL_TYPE; j++) {
			hero->frame_length[j] = lengths[j];
			hero->frame_width[j] = widths[j];
			hero->frame_height[j] = heights[j];
			if (j == 0) hero->frame_total_height[j] = 0;
			else hero->frame_total_height[j] = heights[j - 1] + hero->frame_total_height[j - 1];
			hero->frame_biasx[j] = biasx[j];
			hero->frame_biasy[j] = biasy[j];
		}
	}
	else if (type == HERO_YAGAMI) {
		int lengths[TOTAL_TYPE] = { 9, 10, 19, 11, 30, 13, 16, 11, 9 },
			widths[TOTAL_TYPE] = { 74, 68, 149, 88, 195, 68, 265, 125, 70 },
			heights[TOTAL_TYPE] = { 102, 104, 203, 102, 209, 190, 114, 103, 107 },
			biasx[TOTAL_TYPE] = { 1, -9, 36, -13, -62, -2, 87, 27, -12 },
			biasy[TOTAL_TYPE] = { 0, -1, -49, 0, -54, -44, -3, -1, -3 };
		hero->img = bmp_Unit_yagami;
		for (int j = 0; j < TOTAL_TYPE; j++) {
			hero->frame_length[j] = lengths[j];
			hero->frame_width[j] = widths[j];
			hero->frame_height[j] = heights[j];
			if (j == 0) hero->frame_total_height[j] = 0;
			else hero->frame_total_height[j] = heights[j - 1] + hero->frame_total_height[j - 1];
			hero->frame_biasx[j] = biasx[j];
			hero->frame_biasy[j] = biasy[j];
		}
	}

	hero->state = HERO_STATE_HOLD;
	hero->frame_column = 0;
	hero->x = x;
	hero->y = y;
	hero->vx = 3;
	hero->vy = 1;
	hero->health = health;
	hero->blue = blue;
	hero->hurt = 0;
	hero->is_immune = false;
	hero->is_superimmune = false;
	return hero;
}

// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_STARTMENU) {
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME || button->buttonID == BUTTON_SET)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID >= STAGE_1 && stageID <= STAGE_3) //TODO：添加多个游戏场景
	{
		if (stageID == STAGE_1) {
			currentStage->bg = bmp_Background;
		}
		else if (stageID == STAGE_2) {
			currentStage->bg = bmp_Stage2;
		}
		else if (stageID == STAGE_3) {
			currentStage->bg = bmp_Stage3;
		}
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		heros.clear();
		keyAttackDown = false;
		keyDefenseDown = false;
		keyUtimate1 = false;
		keyUtimate2 = false;
		isAiSkill = false;
		isRedSkill = false;

		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STOP) 
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

		heros.push_back(CreateHero(aiHero, 1000, 500, 100, 100, UNIT_SIDE_BLUE));  
		heros.push_back(CreateHero(myHero, 300, 500, 100, 100, UNIT_SIDE_RED));

	}
	else if (stageID == STAGE_CHOOSE)
	{
		currentStage->bg = bmp_ChooseBG;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		myCount = 4000;
		aiCount = 4001;
		aiType = 0;
		stageType = 0;
		
		myHero = HERO_KULA;
		aiHero = HERO_KYOKUSANAGI;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_FIGHT || button->buttonID == BUTTON_BACK
				|| button->buttonID == BUTTON_LARROW || button->buttonID == BUTTON_LARROW2
				|| button->buttonID == BUTTON_RARROW || button->buttonID == BUTTON_RARROW2
				|| button->buttonID == BUTTON_STAGE || button->buttonID == BUTTON_AI )
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}

// 设置按钮处理函数
void SetUpdate(HWND hWnd) {
	setOpen = true;
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_HELP or button->buttonID == BUTTON_MENU or button->buttonID == BUTTON_SET)
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

// 帮助按钮处理函数
void HelpUpdate(HWND hWnd) {
	helpOpen = true;
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_CONTINUE)
		{
			button->visible = true;
		}
		else if (button->buttonID == BUTTON_STOP && (STAGE_1 <= currentStage->stageID && currentStage->stageID <= STAGE_3))
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

// 暂停按钮处理函数
void StopUpdate(HWND hWnd) {
	stopOpen = true;
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_MENU
			or button->buttonID == BUTTON_HELP
			or button->buttonID == BUTTON_RESUME
			or button->buttonID == BUTTON_STOP)
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
	//关闭计时器
	currentStage->timerOn = false;
	InvalidateRect(hWnd, NULL, FALSE);
}

// 恢复按钮处理函数
void ResumeUpdate(HWND hWnd) {
	currentStage->timerOn = true;
	keyAttackDown = false;
	keyDefenseDown = false;
	keyUtimate1 = false;
	keyUtimate2 = false;
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_STOP)
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
}

// 游戏结束处理函数
void GameOverUpdate(int result) {
	currentStage->timerOn = false;
	if (result == RESULT_WIN)
		winOpen = true;
	else loseOpen = true;
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_CONTINUE || button->buttonID == BUTTON_STOP)
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
}

// 选择英雄按钮处理函数
void ChooseUpdate(HWND hWnd) {
	myHero = heroList[myCount % HERO_NUM];
	aiHero = heroList[aiCount % HERO_NUM];
	InvalidateRect(hWnd, NULL, FALSE);
}

// 刷新单位状态函数
void UpdateUnits(HWND hWnd)
{
	for (int i = 0; i < heros.size(); i++) {
		Hero* hero = heros[i];
		switch (hero->team) {
		case UNIT_SIDE_RED:
			if (aiType == 4) RedBehaviour(hero);
			else MyBehaviour(hero);
			break;
		case UNIT_SIDE_BLUE:
			AiBehaviour(hero);
			break;
		}
	}
}

//AI英雄行为函数
void AiBehaviour(Hero* hero) {
	int state, inverse = 0;
	if (hero->state >= UNIT_STATE_INVERSE) {
		state = hero->state - UNIT_STATE_INVERSE;
		inverse = 1;
	}
	else state = hero->state;

	//播放当前状态下的帧,在帧末尾判断是否需要状态变化
	if (hero->frame_column >= hero->frame_length[state] - 1) {
		hero->frame_column = 0;
		if (state == HERO_STATE_DIE) {
			GameOverUpdate(RESULT_WIN);
		}
		isAiSkill = false;
		SkillEnd(hero, inverse, state);
	}
	//帧播放速度
	else {
		//播放速度可作为难度设定之一
		hero->frame_column += 1 / 2.0;
	}

	// 死亡判定，打断帧
	if (hero->health <= 0) {
		if (state != HERO_STATE_DIE) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_DIE + UNIT_STATE_INVERSE * inverse;
		return;
	}
	//受伤判定，打断帧
	else if (hero->hurt) {
		if (state != HERO_STATE_HURT) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_HURT + UNIT_STATE_INVERSE * inverse;
		SkillRelease(hero, inverse, HERO_STATE_HURT);
		return;
	}
	//出招状态检测
	if (isAiSkill) {
		hero->state = state + UNIT_STATE_INVERSE * inverse;
		SkillRelease(hero,inverse,state);
		return;
	}
	
	//初始化状态
	hero->state = HERO_STATE_HOLD + UNIT_STATE_INVERSE * inverse;

	if (aiType == 0) {
		ai1(hero, inverse, state);
	}
	else if (aiType == 1) {
		ai2(hero, inverse, state);
	}
	else if (aiType == 2) {
		ai3(hero, inverse, state);
	}
	else if (aiType == 3) {
		ai4(hero, inverse, state);
	}
	else if (aiType == 4) {
		ai4(hero, inverse, state);
	}
	SkillRelease(hero, inverse, hero->state- inverse * UNIT_STATE_INVERSE);
}

//Ai1:简单模式,只会普攻和放大招,缺少防御、闪避意识, 攻速很慢
void ai1(Hero* hero,int inverse,int state){
	
	// 目标坐标
	int x = heros[1]->x;
	int ultimate_range = SkillHurtLen(hero->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(heros[1]->type) / 1.5 -50;
	int attack_range = SkillHurtLen(hero->type, HERO_STATE_ATTACK) + HeroHalfwidth(heros[1]->type) / 1.5 -30;
	attackInterval--;
	ultimatekInterval--;
	
	// 向左转
	if (hero->x - x > 0) {
		inverse = 1;
		if (hero->x - x > attack_range) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			//hero->x -= hero->vx; 
			hero->x = XChange(hero->x, -hero->vx);
			return;
		}
	}
	// 向右转
	else if (hero->x - x <= 0) {
		inverse = 0;
		if (hero->x - x < -attack_range){
			hero->state = HERO_STATE_WALK;
			//hero->x += hero->vx;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
	}

	//敌人在跳跃状态下无法锁定
	if (heros[1]->state == HERO_STATE_JUMP + UNIT_STATE_INVERSE || heros[1]->state == HERO_STATE_JUMP) return;
		
	//攻击大招
	if (ultimatekInterval <= 0 && hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)) {
		if (state != HERO_STATE_ULTIMATE1) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ULTIMATE1);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE1 + UNIT_STATE_INVERSE * inverse;
		//每120帧大招一次
		ultimatekInterval = 360;
		return;
	}
	//普攻
	if (attackInterval <= 0) {
		if (state != HERO_STATE_ATTACK) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ATTACK);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ATTACK + UNIT_STATE_INVERSE * inverse;
		//每40帧普攻一次
		attackInterval = 80;
		return;
	}
}

//Ai2:普通模式,会攻击,寻找最佳攻击位置,防御,攻速较慢
void ai2(Hero* hero, int inverse, int state) {

	// 目标坐标
	int x = heros[1]->x;
	int ultimate_range = SkillHurtLen(hero->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(heros[0]->type) / 1.5 - 50;
	int attack_range = SkillHurtLen(hero->type, HERO_STATE_ATTACK) + HeroHalfwidth(heros[0]->type) / 1.5 - 30;
	int target_attack_range = SkillHurtLen(heros[1]->type, HERO_STATE_ATTACK) + HeroHalfwidth(hero->type) / 1.5;
	int target_ultimate_range = SkillHurtLen(heros[1]->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(hero->type) / 1.5;
	
	attackInterval--;
	ultimatekInterval--;
	defenceInterval--;
	
	// 向左转
	if (hero->x - x > 0) {
		inverse = 1;
		//普攻距离
		if ((hero->x - x > attack_range && ultimatekInterval >= 0) || 
			(hero->x - x > attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			//hero->x -= hero->vx;
			hero->x = XChange(hero->x, -hero->vx);
			return;
		}
		//大招距离
		else if (hero->x - x > ultimate_range) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			//hero->x -= hero->vx;
			hero->x = XChange(hero->x, -hero->vx);
			return;
		}
	}
	// 向右转
	else if (hero->x - x <= 0) {
		inverse = 0;
		if ((hero->x - x < -attack_range && ultimatekInterval >= 0) || 
			(hero->x - x < -attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK;
			//hero->x += hero->vx;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
		else if (hero->x - x < -ultimate_range) {
			hero->state = HERO_STATE_WALK;
			//hero->x += hero->vx;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
	}
	
	//敌人跳跃时无法锁定
	if (heros[1]->state == HERO_STATE_JUMP + UNIT_STATE_INVERSE || heros[1]->state == HERO_STATE_JUMP) return;
	

	//大招
	if (ultimatekInterval <= 0 && hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)) {
		if (state != HERO_STATE_ULTIMATE1) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ULTIMATE1);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE1 + UNIT_STATE_INVERSE * inverse;
		ultimatekInterval = 10;
		return;
	}
	//普攻
	if (attackInterval <= 0) {
		if (state != HERO_STATE_ATTACK) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ATTACK);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ATTACK + UNIT_STATE_INVERSE * inverse;
		attackInterval = 40;
		return;
	}
	//防御触发条件
	if ((abs(hero->x - x) <= target_attack_range &&
		abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 70 &&
		//heros[1]->health - hero->health > 50 &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		//hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1) &&
		// (heros[1]->state == HERO_STATE_ATTACK || heros[1]->state == UNIT_STATE_INVERSE + HERO_STATE_ATTACK) &&
		defenceInterval <= 0) ||
		(abs(hero->x - x) <= target_ultimate_range) &&
		abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 50 &&
		heros[1]->blue >= SkillBlue(heros[1]->type, HERO_STATE_ULTIMATE1) &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		//hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1) &&
		defenceInterval <= 0) {
		if (state != HERO_STATE_DEFENCE) {
			hero->frame_column = 0;
			isAiSkill = true;
		}
		hero->state = HERO_STATE_DEFENCE + UNIT_STATE_INVERSE * inverse;
		defenceInterval = 5;
		return;
	}
}

//Ai3:中等模式,会攻击和防御和闪避,寻找最佳攻击位置，攻速正常
void ai3(Hero* hero, int inverse, int state) {

	// 目标坐标
	int x = heros[1]->x;
	int ultimate_range = SkillHurtLen(hero->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(heros[0]->type) / 1.5 - 50;
	int attack_range = SkillHurtLen(hero->type, HERO_STATE_ATTACK) + HeroHalfwidth(heros[0]->type) / 1.5 - 30;
	int target_attack_range = SkillHurtLen(heros[1]->type, HERO_STATE_ATTACK) + HeroHalfwidth(hero->type) / 1.5;
	int target_ultimate_range = SkillHurtLen(heros[1]->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(hero->type) / 1.5;

	attackInterval--;
	ultimatekInterval--;
	defenceInterval--;

	// 向左转
	if (hero->x - x > 0) {
		inverse = 1;
		//普攻距离
		if ((hero->x - x > attack_range && ultimatekInterval >= 0) ||
			(hero->x - x > attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			//hero->x -= hero->vx;
			hero->x = XChange(hero->x, -hero->vx);
			return;
		}
		//大招距离
		else if (hero->x - x > ultimate_range) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			//hero->x -= hero->vx;
			hero->x = XChange(hero->x, -hero->vx);
			return;
		}
	}
	// 向右转
	else if (hero->x - x < 0) {
		inverse = 0;
		if ((hero->x - x < -attack_range && ultimatekInterval >= 0) ||
			(hero->x - x < -attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK;
			//hero->x += hero->vx;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
		else if (hero->x - x < -ultimate_range) {
			hero->state = HERO_STATE_WALK;
			//hero->x += hero->vx;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
	}

	//敌人跳跃时无法锁定
	if (heros[1]->state == HERO_STATE_JUMP + UNIT_STATE_INVERSE || heros[1]->state == HERO_STATE_JUMP) return;


	//大招
	if (ultimatekInterval <= 0 && hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)) {
		if (state != HERO_STATE_ULTIMATE1) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ULTIMATE1);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE1 + UNIT_STATE_INVERSE * inverse;
		ultimatekInterval = 0;
		return;
	}
	//闪避
	if ((	abs(hero->x - x) <= target_attack_range 
			&& abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 
			&& heros[1]->health - hero->health > 40 
			&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)	) ||
		(	abs(hero->x - x) <= target_attack_range
			&& abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 
			&& hero->health < 30 
			&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)	 ) ||
		(	abs(hero->x - x) <= target_attack_range) 
			&& abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2  
			&& hero->health < 50 
			&& heros[1]->blue >= SkillBlue(heros[1]->type, HERO_STATE_ULTIMATE1)  
			&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2		) 
		//&&hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)
		) {
		if (state != HERO_STATE_ULTIMATE2) {
			hero->frame_column = 0;
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE2 + UNIT_STATE_INVERSE * inverse;
		return;
	}
	//普攻
	if (attackInterval <= 0) {
		if (state != HERO_STATE_ATTACK) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ATTACK);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ATTACK + UNIT_STATE_INVERSE * inverse;
		attackInterval = 30;
		return;
	}
	
	//防御触发条件
	if ((abs(hero->x - x) <= target_attack_range &&
		abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 70 &&
		//heros[1]->health - hero->health > 50 &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		//hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1) &&
		//hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE2) &&
		defenceInterval <= 0) ||
		(abs(hero->x - x) <= target_ultimate_range) &&
		abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 50 &&
		heros[1]->blue >= SkillBlue(heros[1]->type, HERO_STATE_ULTIMATE1) &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		//hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1) &&
		defenceInterval <= 0) {
		if (state != HERO_STATE_DEFENCE) {
			hero->frame_column = 0;
			isAiSkill = true;
		}
		hero->state = HERO_STATE_DEFENCE + UNIT_STATE_INVERSE * inverse;
		defenceInterval = 5;
		return;
	}
	//法力不足,血量不足, 跳跃逃遁
}

//Ai4:困难模式,会攻击和防御和闪避,跳跃逼近,寻找最佳攻击位置,攻速较快
void ai4(Hero* hero, int inverse, int state) {

	// 目标坐标
	int x = heros[1]->x;
	int ultimate_range = SkillHurtLen(hero->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(heros[0]->type) / 1.5 - 50;
	int attack_range = SkillHurtLen(hero->type, HERO_STATE_ATTACK) + HeroHalfwidth(heros[0]->type) / 1.5 - 30;
	int target_attack_range = SkillHurtLen(heros[1]->type, HERO_STATE_ATTACK) + HeroHalfwidth(hero->type) / 1.5;
	int target_ultimate_range = SkillHurtLen(heros[1]->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(hero->type) / 1.5;

	attackInterval--;
	ultimatekInterval--;
	defenceInterval--;

	// 向左转
	if (hero->x - x > 0) {
		inverse = 1;
		//普攻距离
		if ((hero->x - x > attack_range && ultimatekInterval >= 0) ||
			(hero->x - x > attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			hero->x = XChange(hero->x, -hero->vx);
			//hero->x -= hero->vx;
			//isAiSkill = true;
			return;
		}
		//大招距离
		else if (hero->x - x > ultimate_range) {
			hero->state = HERO_STATE_JUMP + UNIT_STATE_INVERSE;
			hero->x = XChange(hero->x, -3 * hero->vx);
			//hero->x -= 3*hero->vx;
			//isAiSkill = true;
			return;
		}
	}
	// 向右转
	else if (hero->x - x <= 0) {
		inverse = 0;
		if ((hero->x - x < -attack_range && ultimatekInterval >= 0) ||
			(hero->x - x < -attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
		else if (hero->x - x < -ultimate_range) {
			hero->state = HERO_STATE_JUMP;
			hero->x = XChange(hero->x, 3 * hero->vx);
			return;
		}
	}

	//敌人跳跃时无法锁定
	//if (heros[1]->state == HERO_STATE_JUMP + UNIT_STATE_INVERSE || heros[1]->state == HERO_STATE_JUMP) return;


	//大招
	if (ultimatekInterval <= 0 && hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)) {
		if (state != HERO_STATE_ULTIMATE1) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ULTIMATE1);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE1 + UNIT_STATE_INVERSE * inverse;
		ultimatekInterval = 0;
		return;
	}
	//闪避
	if ((abs(hero->x - x) <= target_attack_range
		&& abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2
		&& heros[1]->health - hero->health > 40
		&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)) ||
		(abs(hero->x - x) <= target_attack_range
			&& abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2
			&& hero->health < 30
			&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)) ||
		(abs(hero->x - x) <= target_attack_range)
		&& abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2
		&& hero->health < 50
		&& heros[1]->blue >= SkillBlue(heros[1]->type, HERO_STATE_ULTIMATE1)
		&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)
		//&&hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)
		) {
		if (state != HERO_STATE_ULTIMATE2) {
			hero->frame_column = 0;
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE2 + UNIT_STATE_INVERSE * inverse;
		return;
	}
	//普攻
	if (attackInterval <= 0) {
		if (state != HERO_STATE_ATTACK) {
			hero->frame_column = 0;
			CollisionJudge(heros[0], heros[1], inverse, HERO_STATE_ATTACK);
			isAiSkill = true;
		}
		hero->state = HERO_STATE_ATTACK + UNIT_STATE_INVERSE * inverse;
		attackInterval = 10;
		return;
	}
	//防御触发条件
	if ((abs(hero->x - x) <= target_attack_range &&
		abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 70 &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		defenceInterval <= 0) ||
		(abs(hero->x - x) <= target_ultimate_range) &&
		abs(heros[1]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 50 &&
		heros[1]->blue >= SkillBlue(heros[1]->type, HERO_STATE_ULTIMATE1) &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		defenceInterval <= 0) {
		if (state != HERO_STATE_DEFENCE) {
			hero->frame_column = 0;
			isAiSkill = true;
		}
		hero->state = HERO_STATE_DEFENCE + UNIT_STATE_INVERSE * inverse;
		defenceInterval = 0;
		return;
	}
}

//AI对打时红方行为函数
void RedBehaviour(Hero* hero) {
	int state, inverse = 0;
	if (hero->state >= UNIT_STATE_INVERSE) {
		state = hero->state - UNIT_STATE_INVERSE;
		inverse = 1;
	}
	else state = hero->state;

	//播放当前状态下的帧,在帧末尾判断是否需要状态变化
	if (hero->frame_column >= hero->frame_length[state] - 1) {
		hero->frame_column = 0;
		if (state == HERO_STATE_DIE) {
			GameOverUpdate(RESULT_LOSE);
		}
		isRedSkill = false;
		SkillEnd(hero, inverse, state);
	}
	//帧播放速度
	else {
		//播放速度可作为难度设定之一
		hero->frame_column += 1 / 2.0;
	}

	// 死亡判定，打断帧
	if (hero->health <= 0) {
		if (state != HERO_STATE_DIE) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_DIE + UNIT_STATE_INVERSE * inverse;
		return;
	}
	//受伤判定，打断帧
	else if (hero->hurt) {
		if (state != HERO_STATE_HURT) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_HURT + UNIT_STATE_INVERSE * inverse;
		SkillRelease(hero, inverse, HERO_STATE_HURT);
		return;
	}
	//出招状态检测
	if (isRedSkill) {
		hero->state = state + UNIT_STATE_INVERSE * inverse;
		SkillRelease(hero, inverse, state);
		return;
	}

	//初始化状态
	hero->state = HERO_STATE_HOLD + UNIT_STATE_INVERSE * inverse;
	ai5(hero, inverse, state);
	SkillRelease(hero, inverse, hero->state - inverse * UNIT_STATE_INVERSE);
}

//Ai5:机器对打的红方Ai
void ai5(Hero* hero, int inverse, int state) {

	// 目标坐标
	int x = heros[0]->x;
	int ultimate_range = SkillHurtLen(hero->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(heros[1]->type) / 1.5 - 50;
	int attack_range = SkillHurtLen(hero->type, HERO_STATE_ATTACK) + HeroHalfwidth(heros[1]->type) / 1.5 - 30;
	int target_attack_range = SkillHurtLen(heros[0]->type, HERO_STATE_ATTACK) + HeroHalfwidth(hero->type) / 1.5;
	int target_ultimate_range = SkillHurtLen(heros[0]->type, HERO_STATE_ULTIMATE1) + HeroHalfwidth(hero->type) / 1.5;
	redAttackInterval--;
	
	// 向左转
	if (hero->x - x > 0) {
		inverse = 1;
		//普攻距离
		if ((hero->x - x > attack_range && ultimatekInterval >= 0) ||
			(hero->x - x > attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK + UNIT_STATE_INVERSE;
			hero->x = XChange(hero->x, -hero->vx);
			//isAiSkill = true;
			return;
		}
		//大招距离
		else if (hero->x - x > ultimate_range) {
			hero->state = HERO_STATE_JUMP + UNIT_STATE_INVERSE;
			hero->x = XChange(hero->x, -3 * hero->vx);
			//isAiSkill = true;
			return;
		}
	}
	// 向右转
	else if (hero->x - x <= 0) {
		inverse = 0;
		if ((hero->x - x < -attack_range && ultimatekInterval >= 0) ||
			(hero->x - x < -attack_range && hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1))) {
			hero->state = HERO_STATE_WALK;
			hero->x = XChange(hero->x, hero->vx);
			return;
		}
		else if (hero->x - x < -ultimate_range) {
			hero->state = HERO_STATE_JUMP;
			hero->x = XChange(hero->x, 3 * hero->vx);
			//isAiSkill = true;
			return;
		}
	}

	//敌人跳跃时无法锁定
	//if (heros[1]->state == HERO_STATE_JUMP + UNIT_STATE_INVERSE || heros[1]->state == HERO_STATE_JUMP) return;


	//大招
	if (hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE1)) {
		if (state != HERO_STATE_ULTIMATE1) {
			hero->frame_column = 0;
			CollisionJudge(hero, heros[0], inverse, HERO_STATE_ULTIMATE1);
			isRedSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE1 + UNIT_STATE_INVERSE * inverse;
		//ultimatekInterval = 0;
		return;
	}
	//闪避
	if ((abs(hero->x - x) <= target_attack_range
		&& abs(heros[0]->state - hero->state) >= UNIT_STATE_INVERSE / 2
		&& heros[0]->health - hero->health > 40
		&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)) ||
		(abs(hero->x - x) <= target_attack_range
			&& abs(heros[0]->state - hero->state) >= UNIT_STATE_INVERSE / 2
			&& hero->health < 30
			&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)) ||
		(abs(hero->x - x) <= target_attack_range)
		&& abs(heros[0]->state - hero->state) >= UNIT_STATE_INVERSE / 2
		&& hero->health < 50
		&& heros[0]->blue >= SkillBlue(heros[0]->type, HERO_STATE_ULTIMATE1)
		&& hero->blue >= SkillBlue(hero->type, HERO_STATE_ULTIMATE2)
		) {
		if (state != HERO_STATE_ULTIMATE2) {
			hero->frame_column = 0;
			isRedSkill = true;
		}
		hero->state = HERO_STATE_ULTIMATE2 + UNIT_STATE_INVERSE * inverse;
		return;
	}
	//普攻
	if (redAttackInterval <= 0) {
		if (state != HERO_STATE_ATTACK) {
			hero->frame_column = 0;
			CollisionJudge(hero, heros[0], inverse, HERO_STATE_ATTACK);
			isRedSkill = true;
		}
		hero->state = HERO_STATE_ATTACK + UNIT_STATE_INVERSE * inverse;
		redAttackInterval = 10;
		return;
	}
	//防御触发条件
	if ((abs(hero->x - x) <= target_attack_range &&
		abs(heros[0]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 70 &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		defenceInterval <= 0) ||
		(abs(hero->x - x) <= target_ultimate_range) &&
		abs(heros[0]->state - hero->state) >= UNIT_STATE_INVERSE / 2 &&
		hero->health < 50 &&
		heros[0]->blue >= SkillBlue(heros[0]->type, HERO_STATE_ULTIMATE1) &&
		hero->blue >= SkillBlue(hero->type, HERO_STATE_DEFENCE) &&
		//hero->blue <= SkillBlue(hero->type, HERO_STATE_ULTIMATE1) &&
		defenceInterval <= 0) {
		if (state != HERO_STATE_DEFENCE) {
			hero->frame_column = 0;
			isRedSkill = true;
		}
		hero->state = HERO_STATE_DEFENCE + UNIT_STATE_INVERSE * inverse;
		defenceInterval = 0;
		return;
	}
}


//我方英雄行为函数
void MyBehaviour(Hero* hero) {

	int state, inverse = 0;
	if (hero->state >= UNIT_STATE_INVERSE) {
		state = hero->state - UNIT_STATE_INVERSE;
		inverse = 1;
	}
	else state = hero->state;
	int one = -(2 * inverse - 1);
	
	//播放当前状态下的帧,在帧末尾判断是否需要状态变化
	if (hero->frame_column >= hero->frame_length[state] - 1) {
		hero->frame_column = 0;
		if (state == HERO_STATE_JUMP) {
			keyUpDown = false;
		}
		else if (state == HERO_STATE_DEFENCE) {
			keyDefenseDown = false;
		}
		else if (state == HERO_STATE_ATTACK) {
			keyAttackDown = false;
		}
		else if (state == HERO_STATE_ULTIMATE1) {
			keyUtimate1 = false;
		}
		else if (state == HERO_STATE_ULTIMATE2) {
			keyUtimate2 = false;
		}
		else if (state == HERO_STATE_DIE) {
			GameOverUpdate(RESULT_LOSE);
		}
		SkillEnd(hero, inverse, state);
		
	}
	//帧播放速度
	else {
		hero->frame_column += 1 / 2.0;
	}

	
	//站立判定
	if (not (keyRightDown || keyLeftDown || keyDownDown || keyUpDown)) {
		hero->state = HERO_STATE_HOLD + UNIT_STATE_INVERSE * inverse;
	}

	//方向键控制
	if (keyRightDown || keyLeftDown) {
		if (keyRightDown) {
			//位移判定
			if (state == HERO_STATE_JUMP) {
				hero->x = XChange(hero->x, 3 * hero->vx);
			}
			else if (state == HERO_STATE_WALK) {
				hero->x = XChange(hero->x, hero->vx);
			}
			//行走状态
			hero->state = HERO_STATE_WALK;
		}
		else if (keyLeftDown) {
			//位移判定
			if (state == HERO_STATE_JUMP) {
				hero->x = XChange(hero->x, -3 * hero->vx);
			}
			else if (state == HERO_STATE_WALK) {
				hero->x = XChange(hero->x, -hero->vx);
			}
			//行走状态
			hero->state = UNIT_STATE_INVERSE + HERO_STATE_WALK;
		}

	}

	// 死亡判定(优先级最高）
	if (hero->health <= 0) {
		if (state != HERO_STATE_DIE) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_DIE + UNIT_STATE_INVERSE * inverse;
	}
	//受伤判定
	else if (hero->hurt) {
		if (state != HERO_STATE_HURT) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_HURT + UNIT_STATE_INVERSE * inverse;
		//不允许囤招,并且会打断施法,但是两个大招不会hurt因此不会被打断,defense有一定概率免hurt
		keyUpDown= keyAttackDown = keyDefenseDown = keyUtimate1 = keyUtimate2 = false;
	}
	//移动大招
	else if (keyUtimate2) {
		if (hero->blue - SkillBlue(hero->type, HERO_STATE_ULTIMATE2) < 0)
		{
			keyUtimate2 = false;
		}
		else {
			if (state != HERO_STATE_ULTIMATE2) {
				hero->frame_column = 0;
			}
			hero->state = HERO_STATE_ULTIMATE2 + UNIT_STATE_INVERSE * inverse;
		}
	}
	//攻击大招
	else if (keyUtimate1) {
		if (hero->blue - SkillBlue(hero->type, HERO_STATE_ULTIMATE1) < 0)
		{
			keyUtimate1 = false;
		}
		else {
			if (state != HERO_STATE_ULTIMATE1) {
				hero->frame_column = 0;
				CollisionJudge(heros[1], heros[0], inverse, HERO_STATE_ULTIMATE1);
			}
			hero->state = HERO_STATE_ULTIMATE1 + UNIT_STATE_INVERSE * inverse;
			//判断是否击中敌人
		}
	}
	//防御判定
	else if (keyDefenseDown) {
		if (hero->blue - SkillBlue(hero->type, HERO_STATE_DEFENCE) < 0)
		{
			keyDefenseDown = false;
		}
		else {
			if (state != HERO_STATE_DEFENCE) {
				hero->frame_column = 0;
			}
			hero->state = HERO_STATE_DEFENCE + UNIT_STATE_INVERSE * inverse;
		}
	}
	//攻击状态
	else if (keyAttackDown) {
		if (state != HERO_STATE_ATTACK) {
			hero->frame_column = 0;
			CollisionJudge(heros[1], heros[0], inverse, HERO_STATE_ATTACK);
		}
		hero->state = HERO_STATE_ATTACK + UNIT_STATE_INVERSE * inverse;
		//判断是否击中敌人
	}
	else if (keyUpDown) {
		if (state != HERO_STATE_JUMP) {
			hero->frame_column = 0;
		}
		hero->state = HERO_STATE_JUMP + UNIT_STATE_INVERSE * inverse;
	}
	SkillRelease(hero,inverse, hero->state - UNIT_STATE_INVERSE * inverse);
	
}

//移动定位
int XChange(int x, int change) {
	if ((x + change) <= L_LIMIT)
		return L_LIMIT;
	else if ((x + change) >= R_LIMIT)
		return R_LIMIT;
	else return x + change;
}

//技能移动距离计算
int SkillMoveLen(int heroType, int heroState) {
	if (heroState == HERO_STATE_ATTACK) {
		switch (heroType) {
		case HERO_KULA:
			return 0;
		case HERO_KYOKUSANAGI:
			return 0;
		case HERO_CLARK:
			return 0;
		case HERO_YAGAMI:
			return 43*3;
		default:
			break;
		}
	}
	else if (heroState == HERO_STATE_ULTIMATE1) {
		switch (heroType) {
		case HERO_KULA:
			return 10*3;
		case HERO_KYOKUSANAGI:
			return 45*3;
		case HERO_CLARK:
			return 41*3;
		case HERO_YAGAMI:
			return 0;
		default:
			break;
		}
	}
	else if (heroState == HERO_STATE_ULTIMATE2) {
		switch (heroType) {
		case HERO_KULA:
			return 270;
		case HERO_KYOKUSANAGI:
			return 300;
		case HERO_CLARK:
			return 240;
		case HERO_YAGAMI:
			return 360;
		default:
			break;
		}
	}
	else return 0;
}

//技能耗蓝量计算
int SkillBlue(int heroType, int heroState) {
	if (heroState == HERO_STATE_ULTIMATE1) {
		switch (heroType) {
		case HERO_KULA:
			return 60;
		case HERO_KYOKUSANAGI:
			return 30;
		case HERO_CLARK:
			return 40;
		case HERO_YAGAMI:
			return 70;
		default:
			break;
		}
	}
	else if (heroState == HERO_STATE_ULTIMATE2) {
		return int(log(SkillMoveLen(heroType, heroState)) * 5);
	}
	else if (heroState == HERO_STATE_DEFENCE) {
		if (heroType == HERO_KULA) return 2;
		else return 0;
	}
	else return 0;
}

//技能伤害距离计算
int SkillHurtLen(int heroType, int heroState) {
	if (heroState == HERO_STATE_ATTACK) {
		switch (heroType) {
		case HERO_KULA:
			return 54*3;
		case HERO_KYOKUSANAGI:
			return 56*3;
		case HERO_CLARK:
			return 99*3;
		case HERO_YAGAMI:
			return 103*3;
		default:
			break;
		}
	}
	else if (heroState == HERO_STATE_ULTIMATE1) {
		switch (heroType) {
		case HERO_KULA:
			return 208*3;
		case HERO_KYOKUSANAGI:
			return 85*3;
		case HERO_CLARK:
			return 140*3;
		case HERO_YAGAMI:
			return 232*3;
		default:
			break;
		}
	}
	else return 0;
}

//技能原始伤害计算
int SkillHurt(int heroType, int heroState) {
	if (heroState == HERO_STATE_ATTACK) {
		switch (heroType) {
		case HERO_KULA:
			return 10;
		case HERO_KYOKUSANAGI:
			return 8;
		case HERO_CLARK:
			return 15;
		case HERO_YAGAMI:
			return 20;
		default:
			break;
		}
	}
	else if (heroState == HERO_STATE_ULTIMATE1) {
		switch (heroType) {
		case HERO_KULA:
			return 35;
		case HERO_KYOKUSANAGI:
			return 25;
		case HERO_CLARK:
			return 30;
		case HERO_YAGAMI:
			return 40;
		default:
			break;
		}
	}
	else return 0;
}

//被击打后伤害计算
int Hurt(int heroType, int heroState, int originHurt) {
	if (heroState == HERO_STATE_DEFENCE) {
		switch (heroType) {
		case HERO_KULA:
			return originHurt * 0.3;
		case HERO_KYOKUSANAGI:
			return originHurt * 0.5;
		case HERO_CLARK:
			return originHurt * 0.7;
		case HERO_YAGAMI:
			return originHurt * 0.8;
		default:
			break;
		}
	}
	else {
		switch (heroType) {
		case HERO_KULA:
			return originHurt;
		case HERO_KYOKUSANAGI:
			return originHurt * 0.7;
		case HERO_CLARK:
			return originHurt * 0.9;
		case HERO_YAGAMI:
			return originHurt * 1.2;
		default:
			break;
		}
	}
}

//概率生成函数
bool Probability(int probability) {
	srand((unsigned)time(NULL));
	int random = rand() % 100;
	if (random < probability) return true;
	else return false;
}

//技能释放时状态变化
void SkillRelease(Hero* hero, int inverse, int heroState) {

	if (heroState == HERO_STATE_ATTACK) {
		if (hero->type == HERO_YAGAMI) 
			hero->is_immune = true;
	}
	else if (heroState == HERO_STATE_DEFENCE) {
		if (hero->type == HERO_CLARK) {
			hero->is_immune = Probability(95);
			hero->is_superimmune =Probability(50);
		}
		else if (hero->type == HERO_YAGAMI)
			hero->is_immune = Probability(20);
		else hero->is_immune =Probability(50);
	}
	else if (heroState == HERO_STATE_ULTIMATE1 || heroState == HERO_STATE_ULTIMATE2 || 
		heroState == HERO_STATE_DIE || heroState == HERO_STATE_HURT) {
		hero->is_superimmune = true;
	}
	else {
		if (hero->type == HERO_CLARK)
			hero->is_immune = Probability(30);
	}

}
	
//技能结束时状态变化
void SkillEnd(Hero * hero, int inverse, int heroState) {
	int one = (inverse * 2 - 1) * (-1);
	//Hero* target;
	//if (hero->team == UNIT_SIDE_RED) target = heros[0];
	//else target = heros[1];
	
	if (heroState == HERO_STATE_ATTACK) {
		//CollisionJudge(hero, target, inverse, heroState);
		if (hero->blue <= 95)
			hero->blue += 5;
		else hero->blue = 100;
		if (hero->type == HERO_YAGAMI) {
			if (hero->health <= 97)
				hero->health += 3;
			else hero->health = 100;
		}
		hero->blue -= SkillBlue(hero->type, heroState);
		hero->x = XChange(hero->x, one * SkillMoveLen(hero->type, heroState));
	}
	else if (heroState == HERO_STATE_ULTIMATE1) {
		//CollisionJudge(hero, target, inverse, heroState);
		if (hero->type == HERO_YAGAMI) {
			if (hero->health <= 80)
				hero->health += 20;
			else hero->health = 100;
		}
		hero->blue -= SkillBlue(hero->type, heroState);
		hero->x = XChange(hero->x, one * SkillMoveLen(hero->type, heroState));
	}
	else if (heroState == HERO_STATE_ULTIMATE2) {
		hero->blue -= SkillBlue(hero->type, heroState);
		hero->x = XChange(hero->x, one * SkillMoveLen(hero->type, heroState));
	}
	else if (heroState == HERO_STATE_DEFENCE) {
		hero->blue -= SkillBlue(hero->type, heroState);
	}
	else if (heroState == HERO_STATE_HURT) {
		hero->health -= hero->hurt;
	}
	hero->hurt = 0;
	hero->is_immune = false;
	hero->is_superimmune = false;
	hero->state = HERO_STATE_HOLD + UNIT_STATE_INVERSE * inverse;
}

//计算英雄宽度
int HeroHalfwidth(int heroType) {
	switch (heroType) {
	case HERO_KULA:
		return HERO_KULA_WIDTH *3 / 2;
	case HERO_KYOKUSANAGI:
		return HERO_KYOKUSANAGI_WIDTH *3 / 2;
	case HERO_CLARK:
		return HERO_CLARK_WIDTH * 3 / 2;
	case HERO_YAGAMI:
		return HERO_YAGAMI_WIDTH * 3 / 2;
	default:
		break;
	}
}

//碰撞检测
void CollisionJudge(Hero* attacker, Hero* target, int inverse, int attackerState) {
	if (target->is_superimmune) return;
	
	int flag = 0;
	int targerState = 0;
	int skillDistance = SkillHurtLen(attacker->type, attackerState)+ HeroHalfwidth(target->type) /1.5;
	
	if (target->state >= UNIT_STATE_INVERSE) {
		targerState = target->state - UNIT_STATE_INVERSE;
	}
	else targerState = target->state;

	if (inverse){
		if (attacker->x - skillDistance <= target->x && attacker->x >= target->x - HeroHalfwidth(target->type)) {
			flag = 1;
		}
	}
	else {
		if (attacker->x + skillDistance  >= target->x && attacker->x <= target->x + HeroHalfwidth(target->type)) {
			flag = 1;
		}
	}
	
	if (flag) {
		if (target->is_immune) {
			if (attackerState == HERO_STATE_ULTIMATE1) {
				target->hurt = Hurt(target->type, targerState, SkillHurt(attacker->type, attackerState));
				
			}
			else return;
		}
		else {
			target->hurt = SkillHurt(attacker->type, attackerState);
			target->hurt = Hurt(target->type, targerState, SkillHurt(attacker->type, attackerState));
		}
	}
	else return;
}

// 选择英雄姓名框函数
HBITMAP SelectHeroName(int heroType) {
	switch (heroType) {
	case HERO_KULA:
		return bmp_Name_kula;
	case HERO_KYOKUSANAGI:
		return bmp_Name_kyokusanagi;
	case HERO_CLARK:
		return bmp_Name_clark;
	case HERO_YAGAMI:
		return bmp_Name_yagami;
	default:
		break;
	}
}

// 选择英雄头像函数
HBITMAP SelectHeroIcon(int heroType, int heroTeam) {
	if (heroTeam == UNIT_SIDE_RED) {
		switch (heroType) {
		case HERO_KULA:
			return bmp_Icon1_kula;
		case HERO_KYOKUSANAGI:
			return bmp_Icon1_kyokusanagi;
		case HERO_CLARK:
			return bmp_Icon1_clark;
		case HERO_YAGAMI:
			return bmp_Icon1_yagami;
		default:
			break;
		}
	}
	else if (heroTeam == UNIT_SIDE_BLUE) {
		switch (heroType) {
		case HERO_KULA:
			return bmp_Icon2_kula;
		case HERO_KYOKUSANAGI:
			return bmp_Icon2_kyokusanagi;
		case HERO_CLARK:
			return bmp_Icon2_clark;
		case HERO_YAGAMI:
			return bmp_Icon2_yagami;
		default:
			break;
		}
	}
	else {
		return NULL;
	}
}

// 选择场景图片函数
HBITMAP SelectStage(int stageType) {
	switch (stageType) {
	case 0:
		return bmp_Alley;
	case 1:
		return bmp_Subway;
	case 2:
		return bmp_Town;
	default:
		break;
	}
}

// 选择AI对手函数
HBITMAP SelectAi(int stageType) {
	switch (stageType) {
	case 0:
		return bmp_Easy;
	case 1:
		return bmp_Normal;
	case 2:
		return bmp_Medium;
	case 3:
		return bmp_Hard;
	case 4:
		return bmp_Ai;
	default:
		break;
	}
}

#pragma endregion


#pragma region 绘图函数
// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	//获取窗口DC
	HDC hdc_window = BeginPaint(hWnd, &ps);

	//创建内存DC 
	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);  //大缓存
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);	//小缓存

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// 绘制背景到缓存
	SelectObject(hdc_loadBmp, currentStage->bg); //可通过此方法加载不同关卡的背景
	//SelectObject(hdc_loadBmp, bmp_Background);

	// 先将背景绘制到屏幕上（最底层先画）
	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU) {
		// 绘制标题
		SelectObject(hdc_loadBmp, bmp_Title);
		TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - TITEL_WIDTH) / 2, 146,
			TITEL_WIDTH, TITEL_HEIGHT,
			hdc_loadBmp, 0, 0, TITEL_WIDTH, TITEL_HEIGHT,
			RGB(100, 100, 100));

		// 绘制界面
		if (setOpen) {
			SelectObject(hdc_loadBmp, bmp_setBG);
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - SET_WIDTH) / 2, 111,
				SET_WIDTH, SET_HEIGHT,
				hdc_loadBmp, 0, 0, SET_WIDTH, SET_HEIGHT,
				RGB(100, 100, 100));
		}
		if (helpOpen) {
			SelectObject(hdc_loadBmp, bmp_HelpBG);
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - HELP_WIDTH) / 2, 111,
				HELP_WIDTH, HELP_HEIGHT,
				hdc_loadBmp, 0, 0, HELP_WIDTH, HELP_HEIGHT,
				RGB(100, 100, 100)); {
			}
		}

	}
	else if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_3) //TODO：添加多个游戏场景
	{

		// 绘制vs
		SelectObject(hdc_loadBmp, bmp_vs);
		TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - VS_WIDTH) / 2, 88,
			VS_WIDTH, VS_HEIGHT,
			hdc_loadBmp, 0, 0, VS_WIDTH, VS_HEIGHT,
			RGB(100, 100, 100));

		// 绘制英雄
		int column, state;
		for (int i = 0; i < heros.size(); i++) {

			// 绘制头像
			Hero* hero = heros[i];
			SelectObject(hdc_loadBmp, SelectHeroIcon(hero->type, hero->team));
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - ICON_WIDTH) * (hero->team - UNIT_SIDE_RED), 38,
				ICON_WIDTH, ICON_HEIGHT,
				hdc_loadBmp, 0, 0, ICON_WIDTH, ICON_HEIGHT,
				RGB(100, 100, 100)); {
			}

			// 绘制血条
			RECT health_bar = { 0 };
			if (hero->team == UNIT_SIDE_RED) {
				health_bar.left = 133;
				if (hero->health > 0) 
					health_bar.right = health_bar.left + (int)(RBAR_WIDTH * hero->health / 100);
				else health_bar.right = 133;
				health_bar.top = 73;
				health_bar.bottom = health_bar.top + BAR_HEIGHT;
			}
			else {
				health_bar.right = 1227;
				if (hero->health > 0)
					health_bar.left = health_bar.right - (int)(RBAR_WIDTH * hero->health / 100);
				else health_bar.left = 1227;
				health_bar.top = 73;
				health_bar.bottom = health_bar.top + BAR_HEIGHT;
			}
			HBRUSH rbrush = CreateSolidBrush(RGB(255, hero->health, 30));
			FillRect(hdc_memBuffer, &health_bar, rbrush);
			DeleteObject(rbrush);

			RECT blue_bar = { 0 };
			if (hero->team == UNIT_SIDE_RED) {
				blue_bar.left = 133;
				if (hero->blue > 0)
					blue_bar.right = blue_bar.left + (int)(BBAR_WIDTH * hero->blue / 100);
				else blue_bar.right = 133;
				blue_bar.top = 106;
				blue_bar.bottom = blue_bar.top + BAR_HEIGHT;
			}
			else if (hero->team == UNIT_SIDE_BLUE) {
				blue_bar.right = 1227;
				if (hero->blue > 0)
					blue_bar.left = blue_bar.right - (int)(BBAR_WIDTH * hero->blue / 100);
				else blue_bar.left = 1227;
				blue_bar.top = 106;
				blue_bar.bottom = blue_bar.top + BAR_HEIGHT;
			}
			HBRUSH bbrush = CreateSolidBrush(RGB(100 - hero->health, 154, 255));
			FillRect(hdc_memBuffer, &blue_bar, bbrush);
			DeleteObject(bbrush);

			// 绘制英雄行为
			if (hero->state >= UNIT_STATE_INVERSE) state = hero->state - UNIT_STATE_INVERSE;
			else state = hero->state;
			int width = hero->frame_width[state],
				height = hero->frame_height[state],
				total_height = hero->frame_total_height[state],
				biasx = hero->frame_biasx[state],
				biasy = hero->frame_biasy[state],
				inverse = 1;
			if (hero->state >= UNIT_STATE_INVERSE) {
				column = width * int(hero->frame_length[state] + hero->frame_column);
				inverse = -1;
			}
			else column = width * int(hero->frame_column);
			SelectObject(hdc_loadBmp, hero->img);	//把对应的帧加载到小缓冲画板
			TransparentBlt(
				hdc_memBuffer, hero->x - 1.5 * width + biasx * 3 * inverse, hero->y - 1.5 * height + biasy * 3, // HERO POSITION IN THE MAP 落在每帧中心
				width * 3, height * 3,   // HERO SIZE
				hdc_loadBmp, column, total_height, width, height, // HERO POSITION IN THE BITMAP
				RGB(255, 255, 255));
		}

		// 绘制界面
		if (winOpen) {
			SelectObject(hdc_loadBmp, bmp_Win);
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - WIN_WIDTH) / 2, 259,
				WIN_WIDTH, WIN_HEIGHT,
				hdc_loadBmp, 0, 0, WIN_WIDTH, WIN_HEIGHT,
				RGB(100, 100, 100)); {
			}
		}
		if (loseOpen) {
			SelectObject(hdc_loadBmp, bmp_Lose);
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - LOSE_WIDTH) / 2, 259,
				LOSE_WIDTH, LOSE_HEIGHT,
				hdc_loadBmp, 0, 0, LOSE_WIDTH, LOSE_HEIGHT,
				RGB(100, 100, 100)); {
			}
		}
		if (stopOpen) {
			SelectObject(hdc_loadBmp, bmp_StopBG);
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - STOP_WIDTH) / 2, 111,
				STOP_WIDTH, STOP_HEIGHT,
				hdc_loadBmp, 0, 0, STOP_WIDTH, STOP_HEIGHT,
				RGB(100, 100, 100)); {
			}
		}
		if (helpOpen) {
			SelectObject(hdc_loadBmp, bmp_HelpBG);
			TransparentBlt(hdc_memBuffer, (WINDOW_WIDTH - HELP_WIDTH) / 2, 111,
				HELP_WIDTH, HELP_HEIGHT,
				hdc_loadBmp, 0, 0, HELP_WIDTH, HELP_HEIGHT,
				RGB(100, 100, 100)); {
			}
		}



	}
	else if (currentStage->stageID == STAGE_CHOOSE) {

		SelectObject(hdc_loadBmp, SelectHeroName(myHero));
		TransparentBlt(hdc_memBuffer, 780, 251,
			NAME_WIDTH, NAME_HEIGHT,
			hdc_loadBmp, 0, 0, NAME_WIDTH, NAME_HEIGHT,
			RGB(100, 100, 100));

		SelectObject(hdc_loadBmp, SelectHeroName(aiHero));
		TransparentBlt(hdc_memBuffer, 780, 502,
			NAME_WIDTH, NAME_HEIGHT,
			hdc_loadBmp, 0, 0, NAME_WIDTH, NAME_HEIGHT,
			RGB(100, 100, 100));
		
		SelectObject(hdc_loadBmp, SelectStage(stageType));
		BitBlt(hdc_memBuffer, 0, 144 + BUTTON_STAGE_HEIGHT, DEMO_WIDTH, DEMO_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

		SelectObject(hdc_loadBmp, SelectAi(aiType));
		BitBlt(hdc_memBuffer, 0, 144 + BUTTON_STAGE_HEIGHT + DEMO_HEIGHT, BUTTON_STAGE_WIDTH, BUTTON_STAGE_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		
	}

	// 绘制按钮到缓存
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (button->buttonID != BUTTON_AI) {
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					button->width, button->height,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(100, 100, 100));
			}
		}
	}

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）

	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src) {

	srand(time(NULL));
	PAINTSTRUCT ps;
	//获取窗口DC
	HDC hdc_window = BeginPaint(hWnd, &ps); //显示器面板

	//创建内存DC 
	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window); //大缓冲
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window); //小缓冲

	//初始化大缓存
	HBITMAP	bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT); //创建HBITMAP
	SelectObject(hdc_memBuffer, bmp_output);  //用bmp_output初始化大缓冲

	//把来自文件的位图数据加载到小缓冲画板
	SelectObject(hdc_loadBmp, bmp_src);

	//把小缓冲画布的图像转移到大缓冲画板
	TransparentBlt(
		hdc_memBuffer, 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		hdc_loadBmp, 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		RGB(255, 255, 255)
	);

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);

	//InvalidateRect(hWnd, NULL, FALSE);
	return bmp_output;
}

#pragma endregion