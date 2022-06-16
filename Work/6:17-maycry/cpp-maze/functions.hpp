// 게임의 타이틀을 출력
void welMsg(){
   std::cout<<"  /\\/\\    __ _  ____  ___"<<"\n";
    std::cout<<" /    \\  / _` ||_  / / _ \\"<<"\n";
    std::cout<<"/ /\\/\\ \\| (_| | / / |  __/"<<"\n";
    std::cout<<"\\/    \\/ \\__,_|/___| \\___|"<<"\n";
    std::cout<<UNDER<<"\n\nplay with WASD keys\n\n"<<RESET;                              
}


// 게임 실행 함수
int run() {
    // 타이틀 출력 후 시작
    welMsg();
    while (1) {
        Move mv; // 각각의 이동은 무브 클래스의 인스턴스
        mv.movement();
        if (mv.endGame()) // 게임이 끝나면 이동횟수를 반환
            return mv.getCount();
    }
}

