import java.awt.Color;
import l4g.Classroom;
import l4g.Grader;
import l4g.Presenter_Mode3;
import l4g.Presenter_Mode4;
import l4g.Presenter_Mode5;
import l4g.common.Classroom_Settings;
import l4g.common.GameNumberManager;
import l4g.customplayers.*;
//import loot.GameFrameSettings;


public class Program
{
	public static void main(String[] args)
	{
		// settings는 강의실 설정(게임 한 판 설정)을 위한 여러 필드들을 가지고 있습니다.
		Classroom_Settings settings = new Classroom_Settings();

		/*
		 * mode 값을 바꿈으로써 게임을 여러 가지 방법으로 실행해 볼 수 있습니다.
		 * 
		 * mode 값이 0이면 콘솔 창을 사용하여 게임 한 판을 진행하며
		 * 매 턴마다 주 플레이어(이 아래에서 여러분이 지정해 둔 플레이어)가 내린 의사 결정의 내용,
		 * 어떤 행동을 했는지, 시야 범위에서 어떤 사건들이 발생했는지를 출력하고,
		 * 턴 종료시 그 플레이어의 현재 상태 및 점수를 출력한 다음
		 * 엔터 키를 입력받을 때까지 게임을 일시 정지합니다.
		 * 게임이 끝나면 첫 플레이어의 학점을 출력합니다.
		 * 
		 * mode 값이 1이면 콘솔 창을 사용하여 게임 한 판을 진행하며
		 * 매 턴마다 모든 행동, 사건 정보를 출력하고,
		 * 턴 종료시 모든 플레이어의 현재 상태 및 점수를 출력한 다음
		 * 엔터 키를 입력받을 때까지 게임을 일시 정지합니다.
		 * 게임이 끝나면 모든 플레이어의 학점을 출력합니다.
		 * 
		 * mode 값이 2면 콘솔 창을 사용하여 임의의 게임 번호들을 통해 게임 1,000판을 진행하며
		 * 게임이 모두 끝나면 각 부문별 순위 및 기록을 출력한 다음
		 * 주 플레이어(이 아래에서 여러분이 지정해 둔 플레이어)의 기록을 출력합니다.
		 * 
		 * mode 값이 3이면 테스트용 Presenter를 사용하여 게임 한 판을 진행하며
		 * 이를 통해 주 플레이어(이 아래에서 여러분이 지정해 둔 플레이어)가 획득할 수 있는 정보들을 매 턴마다 시각적으로 살펴 볼 수 있습니다.
		 * 게임이 끝나면 콘솔 창에 그 플레이어의 학점을 출력합니다.
		 * 게임이 끝난 이후에도 엔터 키를 치면 또 다시 시작할 수 있습니다.
		 * 
		 * mode 값이 4이면 경연용 Presenter를 사용하여 게임 한 판 및 100,000판을 진행하며
		 * 모든 게임이 끝나면 콘솔 창에 주 플레이어(이 아래에서 여러분이 지정해 둔 플레이어)의 학점을 출력합니다.
		 * 게임이 끝난 이후에도 엔터 키를 치면 또 다시 시작할 수 있습니다.
		 * 
		 * mode 값이 5면 플레이용 Presenter를 사용하여 여러분이 직접 게임 한 판을 진행할 수 있습니다.
		 * 구체적으로, 이 아래에서 처음 등록한 플레이어를 제외하고, 그 플레이어 대신 여러분이 직접 키보드 / 마우스를 사용하여 게임에 참여합니다.
		 * 게임이 끝난 이후에도 엔터 키를 치면 또 다시 시작할 수 있습니다.
		 */

		int mode = 5;



		/*
		 * 아래의 게임 번호를 -1이 아닌 다른 값으로 설정하면
		 * mode값이 0, 1, 3, 4, 5일 때
		 * 항상 해당 게임 번호를 사용하여 게임을 진행합니다.
		 * 주의: 게임 번호는 long 형식이므로 적을 때 뒤에 L을 꼭 붙여 주세요.
		 * 
		 * TODO 아래에 여러분이 돌려 보고 싶은 게임 번호를 적어 주세요. 또는, 임의의 한 게임을 진행해 보려는 경우 -1로 설정해 주세요.
		 */
		settings.game_number = -1L;


		/*
		 * TODO mode 값이 0, 1, 2, 3, 4일 때
		 * 아래의 코드에서 Player_YOURNAMEHERE 부분을 여러분이 작성한 플레이어 클래스 이름으로 바꿔 주세요.
		 * 그렇게 하면 해당 플레이어의 관점에서 각종 정보가 표시됩니다!
		 */
		settings.playerToFocus = Player_YOURNAMEHERE.class;


		/*
		 * 직접 만든 플레이어를 등록하는 부분입니다.
		 * 자신이 만든 플레이어 클래스를 아래의 주석 내용을 참고하여 등록하세요.
		 * (주석 내용을 복붙한 다음 Player_YOURNAMEHERE 대신 여러분의 플레이어 클래스 이름을 넣으면 됩니다)
		 * 
		 * 주의: 같은 클래스를 여러 번 등록하는 것도 가능합니다.
		 * 하지만 이렇게 하는 경우 여러 플레이어가 항상 같은 의사 결정을 하게 될 수 있으니
		 * 가급적 한 클래스는 한 번만 등록하는 것이 좋겠습니다.
		 */

		settings.custom_player_classes.add(Player_YOURNAMEHERE.class);


		/*
		 * 정규 게임에서 NPC(학점 산정에 영향을 주지 않는 플레이어) 수를 설정하는 부분입니다.
		 * 여러분의 플레이어를 테스트할 땐 이 필드의 값은 그냥 0으로 두세요.
		 */
		settings.numberOfNPCs = 0;

		/*
		 * 게임에 참여할 '무법자 Bot 플레이어 수'의 최대값을 변경할 수 있습니다.
		 * 0 이하로 두면 무법자는 게임에 참여하지 않습니다.
		 * 
		 * '정규 게임'에서 이 값은 0으로 설정됩니다.
		 */
		settings.max_numberOfHornDonePlayer = 0;

		/*
		 * 게임에 참여할 Bot 플레이어들의 분포와 순서를 정할 때 사용하는
		 * seed 문자열을 설정하는 부분입니다.
		 * 
		 * 기본값은 "2023"이며
		 * 이를 다른 문자열로 바꾸는 경우 게임에 같이 참여할 Bot 플레이어 목록도 바뀌게 됩니다.
		 * 
		 * 자신의 플레이어를 여러 가지 플레이어 조합 안에서 테스트해 보려는 경우
		 * "2023" 대신 다른 문자열을 설정해 보세요.
		 * 
		 * 주의: 만약 이 문자열을 '빈 문자열' 또는 null로 설정하는 경우
		 * 강의실을 초기화할 때 다시 기본값으로 복구됩니다.
		 */
		settings.seed_for_sample_players = "2023";

		/*
		 * 아래 설정값을 true로 두면
		 * 게임 진행 도중 플레이어가 런타임 예외를 내는 경우
		 * 해당 예외에 대한 정보를 콘솔 창에 출력합니다.
		 * 
		 * 이거 이외에도 settings에는 다양한 설정 옵션들이 들어 있으니
		 * 아래의 각 mode별 실행 부분을 적절히 변경하여
		 * 여러분 입맛에 맞는 테스트를 진행해 볼 수 있습니다.
		 */
		settings.print_errors = false;





		/*
		 * --------------------------------------------------------------------------------------------
		 * 
		 * 이 아래에는 각 모드별 실행 코드가 나열되어 있습니다.
		 * 테스트 환경을 내 입맛대로 설정하고 싶은 게 아니라면
		 * 이 아래에 있는 내용은 안 봐도 됩니다.
		 * 
		 */

		if ( mode == 0 )
		{
			settings.print_focused_player_only = true;
			settings.print_decisions = true;
			settings.print_actions = true;
			settings.print_reactions = true;
			settings.print_playerInfos = true;
			settings.print_scores_at_each_turns = true;
			settings.print_scores_at_the_end = true;

			settings.callback_EndTurn = () -> {
				try
				{
					System.out.print("Press Enter to continue...");
					System.in.skip(System.in.available());
					System.in.read();
				}
				catch ( Exception e )
				{

				}
				return true;
			};

			Classroom classroom = new Classroom(settings);
			classroom.Initialize();
			classroom.Start();
		}

		if ( mode == 1 )
		{
			settings.print_focused_player_only = false;
			settings.print_decisions = false;
			settings.print_actions = false;
			settings.print_reactions = false;
			settings.print_playerInfos = false;
			settings.use_console_mode = true;
			settings.print_scores_at_each_turns = false;
			settings.print_scores_at_the_end = true;

			settings.callback_EndTurn = () -> {
				try
				{
					System.out.print("Press Enter to continue...");
					System.in.skip(System.in.available());
					System.in.read();
				}
				catch ( Exception e )
				{

				}
				return true;
			};

			Classroom classroom = new Classroom(settings);
			classroom.Initialize();
			classroom.Start();
		}

		if ( mode == 2 )
		{
			GameNumberManager numbers = new GameNumberManager(1000);
			numbers.Create(-1);


			Grader grader = new Grader();

			settings.use_console_mode = false;

			Classroom classroom = null;

			for ( int iGame = 0; iGame < 1000; ++iGame )
			{
				if ( iGame % 100 == 0 )
					System.out.println(iGame + " / 1000 games completed...");
				settings.game_number = numbers.data[iGame];
				classroom = new Classroom(settings);
				classroom.Initialize();
				classroom.Start();
				grader.Update(classroom);
			}

			System.out.println("Done.");

			grader.PrintResults(classroom);
			grader.PrintResultsOf(0, classroom);
			grader.PrintBestFinalGrades(classroom);
		}

		if ( mode == 3 )
		{
			settings.print_focused_player_only = true;
			settings.print_decisions = false;
			settings.print_actions = false;
			settings.print_reactions = false;
			settings.print_playerInfos = false;
			settings.print_scores_at_each_turns = false;
			settings.print_scores_at_the_end = true;

			GameFrameSettings gfs = new GameFrameSettings();
			gfs.window_title = "테스트용 Presenter";
			gfs.canvas_width = 800;
			gfs.canvas_height = 600;
			gfs.numberOfButtons = 20;
			gfs.canvas_backgroundColor = Color.lightGray;

			Presenter_Mode3 window = new Presenter_Mode3(gfs, settings);
			window.setVisible(true);
		}

		if ( mode == 4 )
		{
			settings.print_focused_player_only = true;
			settings.print_decisions = false;
			settings.print_actions = false;
			settings.print_reactions = false;
			settings.print_playerInfos = false;
			settings.print_scores_at_each_turns = false;
			settings.print_scores_at_the_end = true;

			
			GameFrameSettings gfs = new GameFrameSettings();
			gfs.window_title = "경연용 Presenter";
			gfs.canvas_width = 840;
			gfs.canvas_height = 600;
			gfs.numberOfButtons = 20;
			gfs.canvas_backgroundColor = Color.lightGray;

			Presenter_Mode4 window = new Presenter_Mode4(gfs, settings);
			window.setVisible(true);
			
			

			
			GameNumberManager numbers = new GameNumberManager(100000);
			numbers.Create("SeedFile/seed.pdf");

			Grader grader = new Grader();
			settings.use_console_mode = false;

			Classroom classroom = null;

			for ( int iGame = 0; iGame < 100000; ++iGame )
			{
				if ( iGame % 1000 == 0 )
					System.out.println(iGame + " / 100000 games completed...");
				settings.game_number = numbers.data[iGame];
				classroom = new Classroom(settings);
				classroom.Initialize();
				classroom.Start();
				grader.Update(classroom);
			}

			System.out.println("Done.");
			
			grader.SaveToCSV("result_100000.csv");
		}

		
		if ( mode == 5 )
		{
			settings.print_focused_player_only = true;
			settings.print_decisions = false;
			settings.print_actions = false;
			settings.print_reactions = false;
			settings.print_playerInfos = false;
			settings.print_scores_at_each_turns = false;
			settings.print_scores_at_the_end = false;
			settings.use_console_mode = false;
			
			// 첫 플레이어를 제거하고 직접 조작 가능한 플레이어 탑재
			settings.custom_player_classes.remove(0);
			
			if ( settings.numberOfNPCs > 0 )
				--settings.numberOfNPCs;
			
			settings.use_ctrlable_player = true;
			
			GameFrameSettings gfs = new GameFrameSettings();
			gfs.window_title = "Left 4 Grade 2023";
			gfs.canvas_width = 840;
			gfs.canvas_height = 600;
			gfs.numberOfButtons = 22;
			gfs.canvas_backgroundColor = Color.lightGray;
			
			Presenter_Mode5 window = new Presenter_Mode5(gfs, settings);
			window.setVisible(true);			
		}
	}
}

