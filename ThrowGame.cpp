#include"frameHeader.h"
#include<string>

void ThrowFromEarthGame::Draw() {

	DrawExtendGraph(0, 0, 640, 480, Handle::BGHandle, FALSE);
	DrawExtendGraph(256, 176, 384, 304, Handle::EarthHandle, TRUE);
	
	DrawRotaGraph((int)XPosition, (int)YPosition, 0.1, BallRadian, Handle::BallHandle, TRUE, TRUE);

	if (WhetherStart) { Draw::DrawXMiddleOriginal(460, "G:終了 S:リセット", Draw::WhiteColor, Draw::sfont, 400); 
	}else { Draw::DrawXMiddleOriginal(460, "Enter:発射 G:終了 ", Draw::WhiteColor, Draw::sfont, 400); }
	
	if (WhetherEscape) DrawEscape();

	DrawSamba();
}

void ThrowFromEarthGame::Initialize() {

	WhetherStart = false;
	WhichCourse = true;
	InitialVelocity = 0.1, XVelocity = 0, XPosition = 320 - EarthRadius, YPosition = 240;
	DistanceFromEarth = EarthRadius,
	GravitationalAccelration = -EarthGravity * EarthRadius*EarthRadius / DistanceFromEarth * DistanceFromEarth;
	YAccelrationVector = 0;
	BallRadian = 3.14159265358979 * 1.5 - BallErrorRadian;

	WhetherEscape = false;
	EscapeSize = 3;

	StartDisplay = false;

}

void ThrowFromEarthGame::FirstCalculate() {

	WhetherVelocityOvers = SeconodUniversalVelocity < InitialVelocity;
	if (WhetherVelocityOvers) {
		YVelocity = InitialVelocity;
	}
	else {
		aphelionLength = (InitialVelocity*InitialVelocity*EarthRadius) / (2 * EarthGravity*EarthRadius - InitialVelocity * InitialVelocity);
		squaredLongAxis = (EarthRadius + aphelionLength)*(EarthRadius + aphelionLength) / 4;
		squaredShortAxis = aphelionLength * EarthRadius;
		aphelionXPosition = 320 + aphelionLength;
	}
	ReferenceTime = GetNowCount();

}

void ThrowFromEarthGame::Calculate() {
	BallCalculate();
	BallRadianCalculate();
}

void ThrowFromEarthGame::JudgeThings() {

	//JudgeWhetherHurtle();
	JudgeWhetherHit();
	JudgeWhetherEscape();
	//JudgeMagnification();
}

void ThrowFromEarthGame::GameReset() {

//	StopSoundMem(Handle::HurtleSoundHandle);
//  StopSoundMem(Handle::EscapeSoundHandle);
}

void ThrowFromEarthGame::ClearDisplay() {
	std::vector<std::unique_ptr<NiconicoComment>> RedCommentVector;

	RedCommentVector.emplace_back(new NiconicoComment("神業", 320, 240, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("世界が救われた", 320, 280, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("勇者", 320, 320, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("SEKAI NO HAJIMARI", 320, 200, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("I'll be back", 320, 160, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("きよきよしい", 320, 120, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("ミサイル半端ないって", 320, 80, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("完全勝利", 320, 40, Draw::RedColor, Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("た　　だ　　い　　ま",320,360, Draw::RedColor,Fixed));
	RedCommentVector.emplace_back(new NiconicoComment("お前がナンバーワンだ",320,400, Draw::RedColor,Fixed));


	RedCommentVector.emplace_back(new NiconicoComment("神降臨", 320,60, Draw::RedColor, Fixed,300));
	RedCommentVector.emplace_back(new NiconicoComment("やったぜ", 320,100 , Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("粉砕☆玉砕☆大喝采", 320, 140, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("予　　定　　調　　和", 320, 180, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("強すぎる", 320, 220, Draw::RedColor, Fixed,300));
	RedCommentVector.emplace_back(new NiconicoComment("やりますねぇ！", 320, 260, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("理　　解　　不　　能", 320, 300, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("ダンス星人涙目www", 320, 340, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("今日からお前は富士山だ！", 320, 380, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("ありがとう", 320, 420, Draw::RedColor, Fixed, 300));
	RedCommentVector.emplace_back(new NiconicoComment("イエス・キリスト", 320,460 , Draw::RedColor, Fixed, 300));


	RedCommentVector.emplace_back(new NiconicoComment("フタエノキワミ　アーッ!", 320,50 , Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("イキスギィ!", 320, 90, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("日米安全保障条約", 320, 130, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("神のみぞ知る", 320, 170, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("カルボニル基", 320, 210, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("やっぱお前だよ", 320, 250, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("流れ変わったな", 320, 290, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("おめでとう", 320, 330, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("シュレディンガーの猫", 320, 370, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("相対性理論", 320, 410, Draw::RedColor, Fixed, 600));
	RedCommentVector.emplace_back(new NiconicoComment("万  有  引  力", 320, 450, Draw::RedColor, Fixed, 600));

	RedCommentVector.emplace_back(new NiconicoComment("ホモは帰れ", 320,70 , Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("大坂 なおみ優勝", 320, 110, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("114514", 320, 150, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("33-4", 320, 190, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("強い(確信)", 320, 230, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("神風特攻隊", 320, 270, Draw::RedColor, Fixed,900));
	RedCommentVector.emplace_back(new NiconicoComment("北海道大丈夫か", 320, 310, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("U.S.A", 320, 350, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("めげるな自衛隊", 320, 390, Draw::RedColor, Fixed, 900));
	RedCommentVector.emplace_back(new NiconicoComment("Visual Studio", 320, 430, Draw::RedColor, Fixed, 900));


	RedCommentVector.emplace_back(new NiconicoComment("なんか書いとけ", 320, 320, Draw::RedColor, Fixed, 1600));



	NiconicoComment *aiai = new NiconicoComment("うおおおおおおおおお", 50);
	NiconicoComment *iuiu = new NiconicoComment("うおおおおおおおおおおおおおおおおおおおおおおおおおおおおおお", 100);


	NiconicoComment::ReferenceTime = GetNowCount();
	while (ProcessMessage() == 0 && !(CheckHitKey(KEY_INPUT_ESCAPE) || CheckHitKey(KEY_INPUT_RETURN))) {

		DrawExtendGraph(0, 0, 640, 480, Handle::BGHandle, FALSE);
		DrawExtendGraph(256, 176, 384, 304, Handle::EarthHandle, TRUE);

		NiconicoComment::TimeDifference = GetNowCount() - NiconicoComment::ReferenceTime;

		aiai->CommentDisplay();
		iuiu->CommentDisplay();

		for (auto& element : RedCommentVector) {

			element->CommentDisplay();
		}/**/


		ScreenFlip();
		if (NiconicoComment::NumberOfComment) continue;
		break;
	}
	delete aiai, iuiu;
	GameEnd = true;

}

void ThrowFromEarthGame::Adjustment() {
	DrawBox(0, 100, 640, 170, GetColor(255, 0, 0), TRUE);
	Draw::DrawXMiddleOriginal(120, "ミサイルを撃ち込んでダンス星人を駆逐しよう!\nミサイルは地球の周りをまわるぞ!", Draw::WhiteColor, Draw::thickexplainfont);
	
	DrawBox(0, 340, 390, 370, Draw::WhiteColor, TRUE);
	DrawStringToHandle(0, 340, "速度を調節してから発射しよう\n", Draw::RedColor, Draw::thickexplainfont);
	DrawStringToHandle(0, 380, "発射速度変え方:↑ ↓\n", Draw::WhiteColor, Draw::sfont);
	DrawStringToHandle(0, 0, "     ～計算用～\n", Draw::WhiteColor, Draw::explainfont);
	DrawStringToHandle(0, 20, "地球は密度が一様で完全な半径64の球。地表面の万有引力の大きさ:9.8*10^(-5)", Draw::WhiteColor, Draw::explainfont);
	DrawStringToHandle(0, 40, "スケール:10^(-5)。ちなみに、時間は10^(8)倍くらいで進みます(確か)", Draw::WhiteColor, Draw::explainfont);
	DrawStringToHandle(0, 60, "あと、座標はいちいち計算しています。", Draw::WhiteColor, Draw::explainfont);


	DrawExtendGraph(0, 450, 30, 480, Handle::DownButtonHandle, TRUE);
	DrawExtendGraph(30, 450, 60, 480, Handle::UpButtonHandle, TRUE);

	TimeDifference = GetNowCount() - ReferenceTime;
	if (TimeDifference>10 && CheckHitKey(KEY_INPUT_UP)) { InitialVelocity += 0.001; ReferenceTime = GetNowCount();; }
	if (TimeDifference>10 && CheckHitKey(KEY_INPUT_DOWN)&&InitialVelocity>0.04545 ) { InitialVelocity -= 0.001; ReferenceTime = GetNowCount();; }


	WhetherMouseInputDown = ((GetMouseInput()&MOUSE_INPUT_LEFT) != 0) && (Mouse::JudgeMousePosition(0, 30, 450, 480));
	WhetherMouseInputUp = ((GetMouseInput()&MOUSE_INPUT_LEFT) != 0) && (Mouse::JudgeMousePosition(30, 60, 450, 480));


	if (TimeDifference>100 && WhetherMouseInputUp) { InitialVelocity += 0.00001; ReferenceTime = GetNowCount();; }
	if (TimeDifference>100 && WhetherMouseInputDown&&InitialVelocity>0.04545) { InitialVelocity -= 0.00001; ReferenceTime = GetNowCount();; }

	//DrawStringToHandle(0,360,"",Draw::WhiteColor,Draw::sfont);
	DrawStringToHandle(0, 415, std::to_string(InitialVelocity).c_str(), Draw::WhiteColor, Draw::sfont);
	//

	DrawExtendGraph(400, 310, 600, 430, Handle::StartButton, FALSE);

	if (((GetMouseInput()&MOUSE_INPUT_LEFT) != 0) && (Mouse::JudgeMousePosition(400, 500,360, 420))) {
		WhetherStart = true; 
		FirstCalculate();
		StartTime = GetNowCount();
	}
}

void ThrowFromEarthGame::BallCalculate() {	
	TimeDifference *= SpeedMagnification;
	PreXV = XVelocity;
	{
		XAccelrationVector = XPosition - 320;
		YAccelrationVector = YPosition - 240;
		DistanceFromEarth = sqrt(XAccelrationVector*XAccelrationVector + YAccelrationVector * YAccelrationVector);
		GravitationalAccelration = -EarthGravity * EarthRadius*EarthRadius / (DistanceFromEarth * DistanceFromEarth);
		XAccelration = (XAccelrationVector / DistanceFromEarth)*GravitationalAccelration;
		XVelocity += XAccelration * TimeDifference/1000;
		XPosition += 1 / 2 * XAccelration*TimeDifference / 1000 * TimeDifference / 1000 + XVelocity * TimeDifference / 1000;
	}

	if (!WhetherVelocityOvers) {

		YPosition = 240 + (sqrt((1.0 - (XPosition - (320.0 + aphelionLength / 2 - EarthRadius / 2)) * (XPosition - (320.0 + aphelionLength / 2 - EarthRadius / 2)) / squaredLongAxis)*squaredShortAxis))*
			(WhichCourse ? 1 : -1);
		if (XPosition <= perihelionXPosition  || XPosition >= aphelionXPosition ) {
			YPosition = 240;
		}

	}
	else {

		YAccelration = (YAccelrationVector / DistanceFromEarth)*GravitationalAccelration;
		YVelocity += YAccelration*TimeDifference/1000;

		YPosition += 1 / 2 * YAccelration*TimeDifference / 1000 * TimeDifference / 1000 + YVelocity * TimeDifference / 1000;
		

		
	}//if(WVO)
	if (!WhetherVelocityOvers&&XPosition <= 320&&(PreXV*XVelocity)<=0) {
		WhichCourse = true;
	}
	else if (!WhetherVelocityOvers&&XPosition >= 320 && (PreXV*XVelocity) <= 0) {
		WhichCourse = false;
	}
}

void ThrowFromEarthGame::JudgeWhetherHurtle() {
	/*if ((XPosition - 320)*(XPosition - 320) + (YPosition - 240) * (YPosition - 240) < EarthRadius*EarthRadius) {

		if (!CheckSoundMem(Handle::HurtleSoundHandle)) {
			PlaySoundMem(Handle::HurtleSoundHandle, DX_PLAYTYPE_BACK);
		}

	}
	else { StopSoundMem(Handle::HurtleSoundHandle); }*/
}

void ThrowFromEarthGame::JudgeWhetherHit() {
	if (XPosition >= 384 - TargetScale && XPosition <= 384 + TargetScale && YPosition >= 240 - TargetScale && YPosition <= 240 + TargetScale)
	{
		//StopSoundMem(Handle::HurtleSoundHandle);
		//StopSoundMem(Handle::EscapeSoundHandle);
		WhetherWin = true;
		ClearDisplay();
	}
}

void ThrowFromEarthGame::JudgeWhetherEscape() {
	if (XPosition > 640 + HalfBallScale || XPosition < 0 - HalfBallScale || YPosition>480 + HalfBallScale || YPosition < 0 - HalfBallScale) {
		//if (!CheckSoundMem(Handle::EscapeSoundHandle)) {
		//	PlaySoundMem(Handle::EscapeSoundHandle, DX_PLAYTYPE_BACK);
		//}
		WhetherEscape = true;
	}
	else {
		WhetherEscape = false;
		EscapeSize = 3;
		//StopSoundMem(Handle::EscapeSoundHandle);
	}
}

/*
void ThrowFromEarthGame::JudgeMagnification() {

	if (CheckHitKey(KEY_INPUT_LEFT)) ScreenMagnification -= 0.01;
	if (ScreenMagnification < 1 && CheckHitKey(KEY_INPUT_RIGHT)) ScreenMagnification += 0.01;
}
*///倍率かけて表示しようとしたときの残骸、余裕があれば作れたかな

void ThrowFromEarthGame::BallRadianCalculate() {
	if ((int)YPosition != 240) {
		BallRadian = (YPosition > 240 ? 3.14159265358979 : 0) - std::atan((XPosition - 320) / (YPosition - 240)) - BallErrorRadian;
	}
	else {
		BallRadian = 3.14159265358979*(XPosition < 320 ? 1.5 : 0.5) - BallErrorRadian;
	}
}

void ThrowFromEarthGame::DrawSamba() {
	
	
	SambaMode = ((int)(SambaCount / 30)) % NumberOfSamba;
	
	DrawExtendGraph(364, 200, 418, 280, Handle::SambaHandle[SambaMode], TRUE);
	SambaCount++;
	if (SambaCount > 100000) SambaCount = 1;
	
}

void ThrowFromEarthGame::DrawEscape() {
	int Escapefont;
	if (EscapeSize < 200) { 
		Escapefont=CreateFontToHandle("富士ポップ",EscapeSize,(int)EscapeSize/3,DX_FONTTYPE_NORMAL);
		Draw::DrawXMiddleOriginal(240, "どこ行くねーん", Draw::RedColor,Escapefont);
		EscapeSize++;
		DeleteFontToHandle(Escapefont);
	}
	else if(WhetherVelocityOvers){
		Draw::DrawXMiddleOriginal(340, "彼は二度と帰ってこなかった...(完)", Draw::WhiteColor,Draw::Deadfont); 
	}

}

