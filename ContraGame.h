#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>


// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数


// TODO:  在此处引用程序需要的其他头文件
#include <vector>
#include <math.h>
#include <imm.h>
#include <gdiplus.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <Commctrl.h>


#pragma comment(lib, "Imm32.lib")

#pragma endregion


#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1360		//游戏窗口宽度
#define WINDOW_HEIGHT			768		//游戏窗口高度
#define TITEL_WIDTH				804		
#define TITEL_HEIGHT			277		
#define HELP_WIDTH				528
#define HELP_HEIGHT				529
#define SET_WIDTH				529
#define SET_HEIGHT				531
#define STOP_WIDTH				530
#define STOP_HEIGHT				529
#define NAME_WIDTH				251
#define NAME_HEIGHT				70
#define VS_WIDTH				62
#define VS_HEIGHT				50
#define ICON_WIDTH				582
#define ICON_HEIGHT				99
#define RBAR_WIDTH				440
#define BBAR_WIDTH				190
#define BAR_HEIGHT				24
#define WIN_WIDTH				682
#define WIN_HEIGHT				250
#define LOSE_WIDTH				662
#define LOSE_HEIGHT				250
#define L_LIMIT				    120
#define R_LIMIT				    1240

#define DEMO_WIDTH				560
#define DEMO_HEIGHT				319


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_CHOOSE            1
#define STAGE_SET               2
#define STAGE_HELP              3
#define STAGE_STOP              4
#define STAGE_WIN               5
#define STAGE_LOSE              6
#define STAGE_1					11		//第一个游戏场景的ID
#define STAGE_2					12
#define STAGE_3					13

#define UNIT_SIZE_X				64		//单位的宽度
#define UNIT_SIZE_Y				64		//单位的高度
#define UNIT_LAST_FRAME			11		//单位的动画帧最大值

//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10001	//蓝方

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击
#define UNIT_STATE_INVERSE      1000    //反转上述动作

//单位方向定义
#define UNIT_DIRECT_RIGHT		0		//向右
#define UNIT_DIRECT_LEFT		1		//向左

//数量定义
#define HERO_NUM				4
#define AI_NUM					5
#define STAGE_NUM				3

//英雄类型定义
#define HERO_KULA               100   //库拉
#define HERO_KYOKUSANAGI        101   //草稚京
#define HERO_CLARK				102   //克拉克
#define HERO_YAGAMI				103   //八神庵

//英雄长宽定义
#define HERO_KULA_WIDTH				42 
#define HERO_KULA_HEIGHT			105   
#define HERO_KYOKUSANAGI_WIDTH      60
#define HERO_KYOKUSANAGI_HEIGHT     103 
#define HERO_CLARK_WIDTH			80
#define HERO_CLARK_HEIGHT			107
#define HERO_YAGAMI_WIDTH			72
#define HERO_YAGAMI_HEIGHT			102 

//英雄状态定义
#define HERO_STATE_HOLD			0		//静止
#define HERO_STATE_WALK			1		//行走
#define HERO_STATE_ATTACK		2		//攻击
#define HERO_STATE_DEFENCE      3       //防御
#define HERO_STATE_DIE			4		//死亡
#define HERO_STATE_JUMP			5		//跳跃
#define HERO_STATE_ULTIMATE1	6		//攻击大招
#define HERO_STATE_ULTIMATE2	7		//移动大招
#define HERO_STATE_HURT         8      //被击打效果

//键盘字母值定义
#define VK_A                    65
#define VK_W                    87
#define VK_S                    83
#define VK_D                    68
#define VK_J                    74
#define VK_K	                75

//其它定义
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		321		//开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		76		//开始游戏按钮高度

#define BUTTON_SET					1002
#define BUTTON_SET_WIDTH			70
#define BUTTON_SET_HEIGHT			70

#define BUTTON_HELP					1003
#define BUTTON_HELP_WIDTH			297
#define BUTTON_HELP_HEIGHT			70

#define BUTTON_MENU					1004
#define BUTTON_MENU_WIDTH			297
#define BUTTON_MENU_HEIGHT			70

#define BUTTON_FIGHT				1005
#define BUTTON_FIGHT_WIDTH			297
#define BUTTON_FIGHT_HEIGHT			70

#define BUTTON_LARROW				1006
#define BUTTON_LARROW2				1016
#define BUTTON_LARROW_WIDTH			72
#define BUTTON_LARROW_HEIGHT		80

#define BUTTON_RARROW				1007
#define BUTTON_RARROW2				1017
#define BUTTON_RARROW_WIDTH			72
#define BUTTON_RARROW_HEIGHT		80

#define BUTTON_STOP					1008
#define BUTTON_STOP_WIDTH			154
#define BUTTON_STOP_HEIGHT			50

#define BUTTON_RESUME				1009
#define BUTTON_RESUME_WIDTH			297
#define BUTTON_RESUME_HEIGHT		70

#define BUTTON_CONTINUE				1010
#define BUTTON_CONTINUE_WIDTH		297
#define BUTTON_CONTINUE_HEIGHT		70

#define BUTTON_BACK				    1011
#define BUTTON_BACK_WIDTH		    75
#define BUTTON_BACK_HEIGHT		    75

#define BUTTON_STAGE				1012
#define BUTTON_STAGE_WIDTH			560	
#define BUTTON_STAGE_HEIGHT			79	

#define BUTTON_AI					1013
#define BUTTON_AI_WIDTH				560
#define BUTTON_AI_HEIGHT			79

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度	

#define RESULT_WIN			666
#define RESULT_LOSE			555

#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};


// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见?是隐藏了吗
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

// 英雄结构体
struct Hero
{
	HBITMAP img;
	int type;				// 英雄类型
	int state;				// 英雄状态（站立、行走、攻击）
	int team;				// 英雄阵营
	float frame_column;		// 当前使用帧所处的列
	int* frame_length;		// 英雄帧序列在每种状态下的长度
	int* frame_width;		// 英雄帧序列在每种状态下的帧宽度
	int* frame_height;		// 英雄帧序列在每种状态下的帧高度
	int* frame_total_height;// 当前使用帧所处的高度（从上到下）
	int* frame_biasx;		// 英雄帧序列在每种状态下的偏置
	int* frame_biasy;		// 英雄帧序列在每种状态下的偏置
 	 
	int x;					// 坐标x
	int y;					// 坐标y
	int vx;					// 速度x
	int vy;					// 速度y
	int health;				// 生命值

	/*待添加其他属性*/
	int blue;				// 法力
	int hurt;			    // 受伤值
	bool is_immune;			// 是否免普攻伤害
	bool is_superimmune;	// 是否免大招伤害
};


//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 刷新单位状态函数
void UpdateUnits(HWND hWnd);

//英雄行为函数
void MyBehaviour(Hero* hero);
void AiBehaviour(Hero* hero);
void RedBehaviour(Hero* hero);

// 不同界面处理函数
void SetUpdate(HWND hWnd);
void StopUpdate(HWND hWnd);
void HelpUpdate(HWND hWnd);
void ResumeUpdate(HWND hWnd);
void ChooseUpdate(HWND hWnd);
void GameOverUpdate(int result);

// 英雄技能相关函数
int SkillMoveLen(int heroType, int heroState);		//技能移动距离计算
int SkillBlue(int heroType, int heroState);		//技能耗蓝量计算
int SkillHurtLen(int heroType, int heroState);		//技能伤害距离计算
int SkillHurt(int heroType, int heroState);		//技能原始伤害计算
int Hurt(int heroType, int heroState, int originHurt);		// 被击打后伤害计算
void SkillRelease(Hero* hero, int inverse, int heroState);		//技能释放时状态变化
void SkillEnd(Hero* hero, int inverse, int heroState);		//技能结束时状态变化

//	碰撞检测函数
void CollisionJudge(Hero* attacker, Hero* target, int inverse, int attackerState);

// 英雄宽度计算函数
int HeroHalfwidth(int heroType); 

// 位移计算函数
int XChange(int x, int change);

// 概率生成函数
bool Probability(int probability);

// AI英雄函数
void ai1(Hero* hero, int inverse, int state);
void ai2(Hero* hero, int inverse, int state);
void ai3(Hero* hero, int inverse, int state);
void ai4(Hero* hero, int inverse, int state);
void ai5(Hero* hero, int inverse, int state);

//选择英雄函数
HBITMAP SelectHeroName(int heroType);
HBITMAP SelectHeroIcon(int heroType, int heroTeam);

#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion