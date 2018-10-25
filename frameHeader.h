#pragma once
#include"DxLib.h"
#include<vector>

enum CommentType{Normal,Fixed,End};
enum GameState {GameTitle = 0, GameMain, GameOver, GameClear,Credit};

class Draw {
public:
	static void LoadFont();
	static int sfont, lfont, mediumfont, explainfont,creditfont,normalfont,fixedfont,Titlefont,Deadfont,thickexplainfont;
	static int WhiteColor, PurpleColor, RedColor, LightBlueColor,GreenColor,YellowColor,BlueColor;
	static void DrawXMiddleOriginal(const int, const std::string, const int, const int, const int x=320);


};

class Handle {
public:
	static void loadFile();
	static int EarthHandle, BGHandle, BallHandle, UpButtonHandle, DownButtonHandle,StartButton;//絵のハンドル
	static int SambaHandle[10];
	//static int HurtleSoundHandle, EscapeSoundHandle;//音のハンドル
};

class Mouse {
public:
	static bool JudgeMousePosition(const int, const int, const int, const int);
	static int XMousePosition, YMousePosition;
};

class Game{

public:
	virtual bool GameMain();

protected:
	virtual void FirstInitialize() = 0;
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Adjustment() = 0;
	virtual void FirstCalculate() = 0;
	virtual void Calculate() = 0;
	virtual void JudgeThings() = 0;
	virtual void GameReset() = 0;
	virtual void ClearDisplay() = 0;


	bool GameEnd, WhetherStart, WhetherWin, StartDisplay = false;
	unsigned int TimeDifference, ReferenceTime, StartTime;// MoveRate;
};

class ThrowFromEarthGame:public Game {
private:
	void FirstInitialize() {};
	void Initialize();
	void Draw();
	void Adjustment();
	void FirstCalculate();
	void Calculate();
	void JudgeThings();
	void GameReset();
	void ClearDisplay();

	void DrawSamba();
	void BallCalculate();
	void JudgeWhetherHurtle();
	void JudgeWhetherHit();
	void JudgeWhetherEscape();
	void BallRadianCalculate();
	void DrawEscape();
	//void JudgeMagnification();


	const double EarthRadius = 64, EarthGravity = 9.8*0.00001,
		SeconodUniversalVelocity = sqrt(2 * EarthGravity*EarthRadius), perihelionXPosition = 320 - EarthRadius;

	double aphelionLength, LongAxis, squaredShortAxis, squaredLongAxis, DistanceFromEarth = EarthRadius,
		GravitationalAccelration = -EarthGravity * EarthRadius*EarthRadius / DistanceFromEarth * DistanceFromEarth;


	bool WhetherMouseInputUp, WhetherMouseInputDown, WhetherVelocityOvers = false, WhichCourse = true,WhetherEscape=false;//右ならtrue

	double  XPosition = 320 - EarthRadius, YPosition = 240, HurtleReferenceTime, HurtleDifference,
		XVelocity, YVelocity, XAccelration, YAccelration, aphelionXPosition,
		XAccelrationVector, YAccelrationVector = 0, BallRadian = 3.14159265358979 * 1.5 - BallErrorRadian;

	const double BallErrorRadian = 0.2776151964;//絵の誤差調整

	const int TargetScale = 25, HalfBallScale = 0;

	unsigned int SambaCount = 1, SambaMode = 0;
	const int NumberOfSamba = 10;

	double InitialVelocity=0.1;	

	double SpeedMagnification = 1000,PreXV;

	int EscapeSize = 3;

};


class NiconicoComment {
	public:
		NiconicoComment(const std::string com,const int Y,const int td=0):comment(com),y(Y),TimeDelay(td){NumberOfComment++;};
		NiconicoComment(const std::string com,const int X,const int Y,const int Color,const CommentType ctype,const int td=100):comment(com),x(X),y(Y),commenttype(ctype),commentcolor(Color),TimeDelay(td){NumberOfComment++;};

		void CommentDisplay();
		static int ReferenceTime,TimeDifference,NumberOfComment;

	private:
		
		int x = 640;
		const int DisplayTime=8*1000,y,TimeDelay,commentcolor=GetColor(255,255,255);
		const std::string comment;
		CommentType commenttype=Normal;

	};

class gameframe {
	//void drawGameTitle();
public:
	void doMainLoop(int);


private:
	
	enum GameMainMode { Select, FromEarth };
	GameMainMode GameMainSelect = Select;
	bool GameResult;

	void drawGameMain();
	void drawGameTitle();
	void drawGameOver();
	void drawGameClear();
	void drawCredit();
	GameState setGameState(GameState);
	
	ThrowFromEarthGame EarthGame;
	
	void initStage() {};
	GameState stage=GameTitle;
	int starttime;




};






