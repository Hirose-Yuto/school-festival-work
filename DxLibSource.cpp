#include "frameHeader.h"
//#include<Math.h>
#include<cmath>
#include<string>

int Draw::sfont, Draw::lfont, Draw::mediumfont, Draw::explainfont, Draw::creditfont, Draw::normalfont, Draw::fixedfont,Draw::Titlefont,Draw::Deadfont,Draw::thickexplainfont;
int Draw::WhiteColor, Draw::PurpleColor, Draw::RedColor, Draw::LightBlueColor,Draw::GreenColor,Draw::YellowColor,Draw::BlueColor;

int Handle::EarthHandle, Handle::BGHandle, Handle::BallHandle, Handle::UpButtonHandle, Handle::DownButtonHandle,Handle::StartButton;
int Handle::SambaHandle[10];//�G�̃n���h��
//int Handle::HurtleSoundHandle, Handle::EscapeSoundHandle;//���̃n���h��

int NiconicoComment::ReferenceTime, NiconicoComment::TimeDifference, NiconicoComment::NumberOfComment=0;

int Mouse::XMousePosition, Mouse::YMousePosition;
//���̉�


void gameframe::doMainLoop(int scmode) {


	ChangeWindowMode(scmode);
	if (DxLib_Init() == -1) {
		return;
	}

	try {
		Handle::loadFile();
		Draw::LoadFont();
	}
	catch(int errorcode){
		std::string errorcode�P = "�G���[���������܂���\n�G���[�R�[�h�F"+std::to_string(errorcode);
		MessageBox(NULL, errorcode�P.c_str(), "���b�Z�[�W", MB_OK);
		return;

	}
	catch (char errorcode[]) {
		std::string errorcode�P(errorcode,strlen(errorcode));
		MessageBox(NULL, errorcode�P.c_str(), "���b�Z�[�W", MB_OK);
		return;
	}
	

	

	//setGameState(GameTitle);


	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		
		

		ClsDrawScreen();
		switch (stage) {
		case GameTitle:
			//clsDx(); printfDx("����������������������������");
			drawGameTitle();
			break;
		case GameMain:
			drawGameMain();
			break;
		case GameOver:
			drawGameOver();
			break;
		case GameClear:
			drawGameClear();
			break;
		case Credit:
			drawCredit();
			break;
		default:
			 Draw::DrawXMiddleOriginal( 200, "�G���[���������܂����I", Draw::WhiteColor, Draw::lfont);
		}

		

		ScreenFlip();
	}

	DxLib::DxLib_End();
}

void gameframe::drawGameTitle() {
	Draw::DrawXMiddleOriginal(175,"Let's Throw!",Draw::PurpleColor,Draw::Titlefont);
	Draw::DrawXMiddleOriginal(300, "S��GAME SELECT", (Mouse::JudgeMousePosition(0, 640, 284, 316) ? Draw::PurpleColor : Draw::WhiteColor), Draw::sfont);
	Draw::DrawXMiddleOriginal(335, "C��CREDIT", (Mouse::JudgeMousePosition(0, 640, 319, 351) ? Draw::GreenColor : Draw::WhiteColor), Draw::sfont);

	if (Mouse::JudgeMousePosition(0, 640, 284, 316) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0) setGameState(GameMain);
	if (Mouse::JudgeMousePosition(0, 640, 319, 351) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0) setGameState(Credit);
	if (CheckHitKey(KEY_INPUT_S)) setGameState(GameMain);
	if(CheckHitKey(KEY_INPUT_C)) setGameState(Credit);
}

void gameframe::drawGameOver() {
	Draw::DrawXMiddleOriginal( 160, "GameOver", Draw::RedColor, Draw::lfont);
	Draw::DrawXMiddleOriginal(300, "PUSH T KEY", (Mouse::JudgeMousePosition(0, 640, 284, 316) ? Draw::YellowColor : Draw::RedColor), Draw::sfont);
	
	if (Mouse::JudgeMousePosition(0, 640, 284, 316) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0) { setGameState(GameTitle); Sleep(250); }
	if (CheckHitKey(KEY_INPUT_T)) setGameState(GameTitle);
}

void gameframe::drawGameClear() {
	Draw::DrawXMiddleOriginal(160, "GameClear", Draw::LightBlueColor, Draw::lfont);
	Draw::DrawXMiddleOriginal(300, "PUSH T KEY", (Mouse::JudgeMousePosition(0, 640, 284, 316) ? Draw::YellowColor : Draw::LightBlueColor), Draw::sfont);

	if (Mouse::JudgeMousePosition(0, 640, 284, 316) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0) { setGameState(GameTitle); Sleep(250); }
	if (CheckHitKey(KEY_INPUT_T)) setGameState(GameTitle);
}

void gameframe::drawCredit() {
	Draw::DrawXMiddleOriginal(20, "�N���W�b�g", Draw::WhiteColor, Draw::sfont);
	Draw::DrawXMiddleOriginal(50, "?JAXA", Draw::WhiteColor, Draw::creditfont);
	// Draw::DrawXMiddleOriginal(77,"", Draw::WhiteColor, Draw::creditfont)

	Draw::DrawXMiddleOriginal(400, "PUSH T KEY TO RETURN", (Mouse::JudgeMousePosition(0, 640, 384, 416) ? Draw::YellowColor : Draw::GreenColor), Draw::sfont);
	
	if (Mouse::JudgeMousePosition(0, 640, 384, 416) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0) setGameState(GameTitle);
	if (CheckHitKey(KEY_INPUT_T)) setGameState(GameTitle);
	}

GameState gameframe::setGameState(GameState fstate) {
	if (stage != fstate) {
		stage = fstate;
		starttime = GetNowCount();
		if (fstate == GameMain) initStage();
	}
	return stage;
}

void Handle::loadFile() {
	BGHandle    = LoadGraph("Picture\\Universe.png "); 
	EarthHandle = LoadGraph("Picture\\Earth1.png");
	BallHandle  = LoadGraph("Picture\\Ball.png");
	UpButtonHandle=LoadGraph("Picture\\UpButton.png");
	DownButtonHandle=LoadGraph("Picture\\DownButton.png");
	StartButton = LoadGraph("Picture\\�X�^�[�g.png");
	
	LoadDivGraph("Picture\\Samba.png",10,10,1,124,180,SambaHandle);
	
	
	//SambaHandleVector.push_back(LoadGraph("Picture\\Samba.png"));

{
		if (BGHandle == -1) {
			throw 10;
		}
		if (EarthHandle == -1) {
			throw 20;
		}
		if (BallHandle == -1) {
			throw 30;
		}
		if (UpButtonHandle == -1) {
			throw 40;
		}
		if (DownButtonHandle == -1) {
			throw 50;
		}
		
		for(int i=0;i<10;i++){
		if (SambaHandle[i]==-1) throw 60+10*i;
		}
	}




/*  HurtleSoundHandle = LoadSoundMem("Sound\\music04.wav");
	EscapeSoundHandle = LoadSoundMem("Sound\\music16.wav");

	{

	if(HurtleSoundHandle==-1){throw 1010;}
	if(EscapeSoundHandle==-1){throw 1020;}

}


	
	*/
	
}

void Draw::LoadFont() {
	sfont = CreateFontToHandle("MS ����", 32, 9, DX_FONTTYPE_NORMAL),
	lfont = CreateFontToHandle("MS ����", 100, 9, DX_FONTTYPE_EDGE),
	mediumfont = CreateFontToHandle("MS ����", 20, 4, DX_FONTTYPE_NORMAL),
	explainfont = CreateFontToHandle("MS ����", 15, 2, DX_FONTTYPE_NORMAL);
	creditfont = CreateFontToHandle("MS ����", 25, 7, DX_FONTTYPE_NORMAL);
	normalfont = CreateFontToHandle("MS ����", 20, 5, DX_FONTTYPE_EDGE);
	fixedfont=CreateFontToHandle("MS ����", 40, 10, DX_FONTTYPE_EDGE);
	Titlefont=CreateFontToHandle("������ Demibold",70,5,DX_FONTTYPE_NORMAL);
	Deadfont= CreateFontToHandle("�˓�s����", 38, 8, DX_FONTTYPE_NORMAL);
	thickexplainfont= CreateFontToHandle("MS ����", 28, 5, DX_FONTTYPE_NORMAL);

	WhiteColor = GetColor(255, 255, 255),
	PurpleColor = GetColor(255, 0, 255),
	RedColor = GetColor(255, 0, 0),
	LightBlueColor = GetColor(0, 255, 255);
	GreenColor = GetColor(0,255,0);
	YellowColor = GetColor(255,255,0);
	BlueColor = GetColor(0, 0, 255);
}



void Draw::DrawXMiddleOriginal(const int y, const std::string message�P, const int color, const int ftype ,const int x) {

	const int size = (int)message�P.size();
	char message[100];
	std::char_traits<char>::copy(message, message�P.c_str(), size + 1);
	const int SideW = GetDrawStringWidthToHandle(message, size, ftype);
	int VerticalW;
	GetFontStateToHandle(NULL, &VerticalW, NULL, ftype);
	DrawStringToHandle(x - SideW / 2, y - VerticalW / 2, message, color, ftype);
}

bool Mouse::JudgeMousePosition(const int x1,const int x2,const int y1,const int y2) {
	GetMousePoint(&XMousePosition, &YMousePosition);

	return x1 <= XMousePosition && XMousePosition <= x2 && y1 <= YMousePosition && YMousePosition <= y2;
}

void gameframe::drawGameMain() {

	/*if (CheckHitKey(KEY_INPUT_C)) setGameState(GameClear);
	if (CheckHitKey(KEY_INPUT_O)) setGameState(GameOver);*/
	
	if (Mouse::JudgeMousePosition(0, 640, 100, 130) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0) GameMainSelect = FromEarth;
	if (CheckHitKey(KEY_INPUT_E)) GameMainSelect = FromEarth;

	switch (GameMainSelect) {
	case FromEarth:
		if (EarthGame.GameMain()) {
			stage = GameClear;
		} else{			
			stage = GameOver;
		}
		GameMainSelect = Select;
		break;

	case Select:
		Draw::DrawXMiddleOriginal(50,"�Q�[���I��",Draw::WhiteColor,Draw::lfont);
		DrawStringToHandle(100, 100, "���L����", (Mouse::JudgeMousePosition(0,640,100,130) ? Draw::LightBlueColor : Draw::YellowColor), Draw::sfont);
		DrawStringToHandle(125,140,"�~�T�C���𔭎˂��ă_���X���l�ɓ��Ă�Q�[���ł��B\nE:�J�n\n", Draw::WhiteColor, Draw::mediumfont);
		DrawStringToHandle(145, 200, "�@�@�`�v�Z�������l�����`\n�n���̔��a��64\n�����ʒu�ł̖��L���͂̑傫����9.8*10^(-5)\n�X�P�[����1.0*10^(-5)�{�ł��B",Draw::WhiteColor,Draw::explainfont);

		break;
		
	default:
		break;
	}

	
	
}

bool Game::GameMain() {

	FirstInitialize();
	WhetherWin = false;

	while (ProcessMessage() == 0 && !GameEnd && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		Draw();

		if (!WhetherStart) {

		restart:
			Adjustment();

			if (CheckHitKey(KEY_INPUT_RETURN)) {
				WhetherStart = true;
				FirstCalculate();
				StartTime = GetNowCount();
			}//if(CHK(RETURN))
		}//if(!WS)
		else {
			if (!StartDisplay) {
				while ((StartTime - GetNowCount()) < 1000&& ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
					Draw();
					Draw::DrawXMiddleOriginal(240, "�X�^�[�g", Draw::RedColor, Draw::lfont);
					ScreenFlip();
				}
				StartDisplay = true;
			}
			
			TimeDifference = GetNowCount() - ReferenceTime;
			ReferenceTime = GetNowCount();

			Calculate();
			JudgeThings();

			if (CheckHitKey(KEY_INPUT_S)) {
				Initialize();
				GameReset();
				goto restart;//if(WheterThrow)�@�̒���
			}
			//�Q�[�����Z�b�g

			//if(TimeDifference>=MoveRate)
		}//if(WS)else


		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_G)) {
			ClearDrawScreen();
			Initialize();
			GameReset();
			while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				Draw::DrawXMiddleOriginal(220, "�{���ɃQ�[�����I�����܂����H", Draw::RedColor, Draw::sfont);
				Draw::DrawXMiddleOriginal(255, "Y���I��          ", (Mouse::JudgeMousePosition(0, 320, 239, 271) ? Draw::BlueColor : Draw::RedColor), Draw::sfont);
				Draw::DrawXMiddleOriginal(255, "           N��������", (Mouse::JudgeMousePosition(321, 640, 239, 271) ? Draw::BlueColor : Draw::RedColor), Draw::sfont);

				ScreenFlip();
				if (CheckHitKey(KEY_INPUT_Y) || (Mouse::JudgeMousePosition(0, 320, 239, 271) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0)) {
					GameEnd = true;
					break;
				}
				if (CheckHitKey(KEY_INPUT_N) || (Mouse::JudgeMousePosition(321, 640, 239, 271) && (GetMouseInput()&MOUSE_INPUT_LEFT) != 0)) {
					goto restart;//if(WheterThrow)�@�̒���
				}
			}
		}
		//�Q�[���I���I��


	}//if(!GE&&CHT(ESCAPE)==0)

	Initialize();
	GameEnd = false;
	//���̂��߂̏�����

	return WhetherWin;

}

void NiconicoComment::CommentDisplay(){

	switch(commenttype){

	case Normal:
		
		if(TimeDelay<=TimeDifference){
			DrawStringToHandle(x, y, comment.c_str(), commentcolor, Draw::normalfont);
			x -= 3;
			if(x<0) {NumberOfComment--; commenttype=End;}
		}
		
		break;

	case Fixed:
		if(TimeDifference<=TimeDelay+DisplayTime){
			if (TimeDelay < TimeDifference) {
				Draw::DrawXMiddleOriginal(y, comment, commentcolor, Draw::fixedfont, x);
			}
		}else{
		NumberOfComment--; commenttype=End;}
		
	case End:

	default:
		break;
}


}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gameframe* gf = new gameframe();
	gf->doMainLoop(TRUE);
	delete gf;

	return 0;				 
}
