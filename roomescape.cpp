#include <bangtal>
using namespace bangtal;


int main()
{
	//장면 생성
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");


	//열쇠 생성
	auto key = Object::create("Images/열쇠.png", scene1, 600, 140);
	key->setScale(0.2f);


	//열쇠 클릭 시
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		key->pick();
		return true;

		});


	//화분 생성
	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);


	//화분 클릭 시
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			flowerpot->locate(scene1, 550, 200);
			flowerpot_moved = true;
		}
		else {
			flowerpot->locate(scene1, 550, 150);
			flowerpot_moved = false;

		}
		
		return true;

		});


	//문1
	auto d1_open = false;
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (d1_open == true) {
			//문이 열려 있을 때 문을 클릭하면 방 이동
			scene2->enter();
		}

		else if (key->isHanded()){ //문닫&열쇠o
			//문이 닫혀 있을 때 문을 클릭하면 문이 열림
			door1->setImage("Images/문-오른쪽-열림.png");
			d1_open = true; //문이 열린 상태임을 알려준다.
		}

		else { //문닫&열쇠x
			showMessage("열쇠가 필요합니다.");
		}

		return true;
		
	});

	//문2
	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;

	});

	//문3
	auto d3_open = false;
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 915, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (d3_open == true) {
			//문이 열려 있을 때 문을 클릭하면 방 이동
			endGame();
		}

		else { //문닫&열쇠x
			door3->setImage("Images/문-오른쪽-열림.png");
			d3_open = true;
		}

		return true;

	});

	//게임 시작
	startGame(scene1);

	return 0;
}