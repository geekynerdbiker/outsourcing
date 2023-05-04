package l4g.customplayers;

import l4g.common.*;

/**
 * 여러분이 새로운 플레이어를 만들기 위해 실제로 작성하게 될 클래스입니다.
 * 
 * @author Racin
 *
 */
public class Player_YOURNAMEHERE extends Player
{
	// TODO#1 Alt + Shift + R을 써서 클래스 이름을 마음에 드는 이름으로 바꾸어 주세요. 클래스 이름과 플레이어 이름은 별개입니다.
	public Player_YOURNAMEHERE(int ID)
	{
		
		// TODO#2 아래의 "이름!" 위치에 여러분이 만들 플레이어의 이름을 넣어 주세요. 클래스 이름과 플레이어 이름은 별개입니다.
		super(ID, "이름!");
		
		// TODO#3 직접 감염을 받으려는 경우 이 필드의 값을 true로, 그렇지 않은 경우 false로 설정하세요.
		// 이 필드의 값 자체는 아무 때나 바꿀 수 있지만 실질적으로 한 게임에 직접 감염이 여러 번 발동되는 경우는 매우 드무니 그냥 여기서 한 번 정해 두고 잊어도 됩니다.
		trigger_acceptDirectInfection = false;
		
		
		// TODO#4 여기까지 왔으면 이제 Developer's Guide 문서와 각 Bot 플레이어 코드를 한 번만 더 읽어 보고 돌아옵시다.

		
	}
	
	/*
	 * TODO#5	이제 여러분이 그려 둔 노트를 보며 아래에 있는 다섯 가지 의사 결정 메서드 정의를 완성하세요.
	 * 			당연히 한 방에 될 리 없으니, 중간중간 코드를 백업해 두는 것이 좋으며,
	 * 			코드 작성이 어려울 땐 아무 부담 없이 강사에게 도움을 요청해 주세요.
	 * 
	 * 			L4G는 여러분의 '생각'을 추구하는 프로젝트지 검색해서 답을 찾는 프로젝트가 아닙니다!
	 * 
	 * 			여러분이 이번 프로젝트에서 투자한 시간만큼, 이후 다른 과제 / 다른 업무에서 뻘짓을 벌이는 시간이 줄어들게 될 것입니다.
	 * 			그러니 자신이 뭔가 멋진 생각을 떠올렸다면, 이를 내 플레이어에 적용하기 위해 아낌 없는 노력을 투자해 보세요.
	 * 
	 * 			제출기한이 되어 황급히 파일을 업로드하고 Eclipse로 돌아와 여러분이 작성한 코드를 돌아 보면,
	 * 			'코드에 노력이란게 묻어 날 수도 있구나'라는 생각이 절로 들게 될 것입니다.
	 */
	
	@Override
	public DirectionCode Survivor_Move()
	{
		DirectionCode result = null;
		
		// Note: 내 플레이어가 생존자 상태일 때 어디로 이동할지 결정하여 return해야 합니다.
		
		return result;
	}

	@Override
	public void Corpse_Stay()
	{
		// Note: 극한을 추구하는 것이 아니라면 이 메서드 정의는 걍 비워 둬도 무방합니다.
	}

	@Override
	public DirectionCode Infected_Move()
	{
		DirectionCode result = null;
		
		// Note: 내 플레이어가 감염체 상태일 때 어디로 이동할지, 또는 가만히 있을지 결정하여 return해야 합니다.

		return result;
	}

	@Override
	public void Soul_Stay()
	{
		if ( turnInfo.turnNumber == 0 )
		{
			/*
			 * Note: 영혼 대기 메서드는 L4G 게임이 시작되면 가장 먼저 호출되는 메서드입니다.
			 * 		 이 if문의 내용은 0턴째에만 실행되므로, 여기서 여러분이 추가로 선언해 둔 필드들의 값을 미리 지정할 수 있습니다. 
			 */
			
		}
	}

	@Override
	public Point Soul_Spawn()
	{
		int result_row = -1;
		int result_column = -1;

		// Note: 내 플레이어가 영혼 상태일 때 어디에 배치할지 결정하여 return해야 합니다.

		return new Point(result_row, result_column);
	}
}
