package l4g;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;

import l4g.common.Constants;

/**
 * 정규 게임의 결과들을 하나하나 입력받아 최종 평점을 산출하는 클래스입니다.
 * 
 * @author Racin
 *
 */
public class Grader
{
	//data의 맨 마지막엔 Player of L4G가 집계됨
	public long[][] data_best;
	public long[][] data_crit;
	
	public int numberOfAppliedGames;
	
	//각 부문별 순위는 top 10만 기록
	public int[][] IDs_winners_best;
	public int[][] IDs_winners_crit;
	
	public long[] criticalGameNumbers;
	
	public Grader()
	{
		data_best = new long[Constants.Total_Players][Classroom.Score_Titles + 1];
		data_crit = new long[Constants.Total_Players][Classroom.Score_Titles + 1];
		
		numberOfAppliedGames = 0;
		
		IDs_winners_best = new int[Classroom.Score_Titles + 1][10];
		IDs_winners_crit = new int[Classroom.Score_Titles + 1][10];
		
		criticalGameNumbers = new long[Constants.Total_Players];
	}
	
	public void Update(Classroom classroom)
	{
		//모든 플레이어에 대해
		for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
		{
			int[] score = classroom.scores[iPlayer];
			
			//각 상태별 점수들 반영
			for ( int iCategory = 0; iCategory < Classroom.Score_Titles; ++iCategory )
			{
				int point = score[iCategory];
				
				if ( point > data_crit[iPlayer][iCategory] )
					data_crit[iPlayer][iCategory] = point;
				
				data_best[iPlayer][iCategory] += point;
			}
			
			//학점 반영
			int grade = classroom.final_grades[iPlayer];
			
			if ( grade > data_crit[iPlayer][Classroom.Score_Titles] )
			{
				//해당 플레이어의 이번 기록이 가장 좋았던 경우 '가장 강했던 게임' 갱신
				criticalGameNumbers[iPlayer] = classroom.gameNumber;
				data_crit[iPlayer][Classroom.Score_Titles] = grade;
			}
			
			data_best[iPlayer][Classroom.Score_Titles] += grade;
		}
		
		//집계가 끝나면 순위 쟤계산
		for ( int iCategory = 0; iCategory <= Classroom.Score_Titles; ++iCategory )
		{
			//재계산을 위해 초기화
			for ( int iRank = 0; iRank < 10; ++iRank )
			{
				IDs_winners_best[iCategory][iRank] = -1;
				IDs_winners_crit[iCategory][iRank] = -1;
			}
			
			//모든 플레이어에 대해
			for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
			{
				//1등 ~ 10등까지의 점수와 비교
				//Best 계열
				for ( int iRank = 0; iRank < 10; ++iRank )
				{
					//해당 등수의 플레이어보다 현재 플레이어의 점수가 더 높다면 갱신
					if ( IDs_winners_best[iCategory][iRank] == -1 || data_best[iPlayer][iCategory] > data_best[IDs_winners_best[iCategory][iRank]][iCategory] )
					{
						//해당 등수 아래로 한 순위씩 내린 다음 갱신
						for ( int iLowerRank = 9; iLowerRank > iRank; --iLowerRank )
						{
							IDs_winners_best[iCategory][iLowerRank] = IDs_winners_best[iCategory][iLowerRank - 1];
						}
						
						IDs_winners_best[iCategory][iRank] = iPlayer;
						break;
					}
				}
				
				//Critical 계열
				for ( int iRank = 0; iRank < 10; ++iRank )
				{	
					//해당 등수의 플레이어보다 현재 플레이어의 점수가 더 높다면 갱신
					if ( IDs_winners_crit[iCategory][iRank] == -1 || data_crit[iPlayer][iCategory] > data_crit[IDs_winners_crit[iCategory][iRank]][iCategory] )
					{
						//해당 등수 아래로 한 순위씩 내린 다음 갱신
						for ( int iLowerRank = 9; iLowerRank > iRank; --iLowerRank )
						{
							IDs_winners_crit[iCategory][iLowerRank] = IDs_winners_crit[iCategory][iLowerRank - 1];
						}
						
						IDs_winners_crit[iCategory][iRank] = iPlayer;
						break;
					}
				}
			}
		}
		
		++numberOfAppliedGames;		
	}

	public void Merge(Grader other)
	{
		//모든 플레이어에 대해
		for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
		{
			//각 상태별 점수들 반영
			for ( int iCategory = 0; iCategory < Classroom.Score_Titles; ++iCategory )
			{
				long point = other.data_crit[iPlayer][iCategory];
				
				if ( point > data_crit[iPlayer][iCategory] )
					data_crit[iPlayer][iCategory] = point;
				
				data_best[iPlayer][iCategory] += other.data_best[iPlayer][iCategory];
			}
			
			//학점 반영
			long grade = other.data_crit[iPlayer][Classroom.Score_Titles];
			
			if ( grade > data_crit[iPlayer][Classroom.Score_Titles] )
			{
				//해당 플레이어의 이번 기록이 가장 좋았던 경우 '가장 강했던 게임' 갱신
				criticalGameNumbers[iPlayer] = other.criticalGameNumbers[iPlayer];
				data_crit[iPlayer][Classroom.Score_Titles] = grade;
			}
			
			data_best[iPlayer][Classroom.Score_Titles] += other.data_best[iPlayer][Classroom.Score_Titles];
		}
		
		//집계가 끝나면 순위 쟤계산
		for ( int iCategory = 0; iCategory <= Classroom.Score_Titles; ++iCategory )
		{
			//재계산을 위해 초기화
			for ( int iRank = 0; iRank < 10; ++iRank )
			{
				IDs_winners_best[iCategory][iRank] = -1;
				IDs_winners_crit[iCategory][iRank] = -1;
			}
			
			//모든 플레이어에 대해
			for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
			{
				//1등 ~ 10등까지의 점수와 비교
				//Best 계열
				for ( int iRank = 0; iRank < 10; ++iRank )
				{
					//해당 등수의 플레이어보다 현재 플레이어의 점수가 더 높다면 갱신
					if ( IDs_winners_best[iCategory][iRank] == -1 || data_best[iPlayer][iCategory] > data_best[IDs_winners_best[iCategory][iRank]][iCategory] )
					{
						//해당 등수 아래로 한 순위씩 내린 다음 갱신
						for ( int iLowerRank = 9; iLowerRank > iRank; --iLowerRank )
						{
							IDs_winners_best[iCategory][iLowerRank] = IDs_winners_best[iCategory][iLowerRank - 1];
						}
						
						IDs_winners_best[iCategory][iRank] = iPlayer;
						break;
					}
				}
				
				//Critical 계열
				for ( int iRank = 0; iRank < 10; ++iRank )
				{	
					//해당 등수의 플레이어보다 현재 플레이어의 점수가 더 높다면 갱신
					if ( IDs_winners_crit[iCategory][iRank] == -1 || data_crit[iPlayer][iCategory] > data_crit[IDs_winners_crit[iCategory][iRank]][iCategory] )
					{
						//해당 등수 아래로 한 순위씩 내린 다음 갱신
						for ( int iLowerRank = 9; iLowerRank > iRank; --iLowerRank )
						{
							IDs_winners_crit[iCategory][iLowerRank] = IDs_winners_crit[iCategory][iLowerRank - 1];
						}
						
						IDs_winners_crit[iCategory][iRank] = iPlayer;
						break;
					}
				}
			}
		}
		
		numberOfAppliedGames += other.numberOfAppliedGames;		
	}
	
	public void PrintResults(Classroom classroom)
	{
		System.out.println("----- Results -----");
		
		System.out.printf("Best Survivor (Max): %s - %d turns\n", classroom.players[IDs_winners_best[0][0]].name, data_best[IDs_winners_best[0][0]][0]);
		System.out.printf("2nd: %s - %d turns\n", classroom.players[IDs_winners_best[0][1]].name, data_best[IDs_winners_best[0][1]][0]);
		System.out.printf("3rd: %s - %d turns\n", classroom.players[IDs_winners_best[0][2]].name, data_best[IDs_winners_best[0][2]][0]);
		System.out.printf("4th: %s - %d turns\n", classroom.players[IDs_winners_best[0][3]].name, data_best[IDs_winners_best[0][3]][0]);
		System.out.printf("5th: %s - %d turns\n", classroom.players[IDs_winners_best[0][4]].name, data_best[IDs_winners_best[0][4]][0]);
		System.out.printf("6th: %s - %d turns\n", classroom.players[IDs_winners_best[0][5]].name, data_best[IDs_winners_best[0][5]][0]);
		System.out.printf("7th: %s - %d turns\n", classroom.players[IDs_winners_best[0][6]].name, data_best[IDs_winners_best[0][6]][0]);
		System.out.printf("8th: %s - %d turns\n", classroom.players[IDs_winners_best[0][7]].name, data_best[IDs_winners_best[0][7]][0]);
		System.out.printf("9th: %s - %d turns\n", classroom.players[IDs_winners_best[0][8]].name, data_best[IDs_winners_best[0][8]][0]);
		System.out.printf("10t: %s - %d turns\n", classroom.players[IDs_winners_best[0][9]].name, data_best[IDs_winners_best[0][9]][0]);
		System.out.printf("Crit.Survivor (Max): %s - %d turns\n", classroom.players[IDs_winners_crit[0][0]].name, data_crit[IDs_winners_crit[0][0]][0]);
		System.out.printf("2nd: %s - %d turns\n", classroom.players[IDs_winners_crit[0][1]].name, data_crit[IDs_winners_crit[0][1]][0]);
		System.out.printf("3rd: %s - %d turns\n", classroom.players[IDs_winners_crit[0][2]].name, data_crit[IDs_winners_crit[0][2]][0]);
		System.out.printf("4th: %s - %d turns\n", classroom.players[IDs_winners_crit[0][3]].name, data_crit[IDs_winners_crit[0][3]][0]);
		System.out.printf("5th: %s - %d turns\n", classroom.players[IDs_winners_crit[0][4]].name, data_crit[IDs_winners_crit[0][4]][0]);
		System.out.printf("6th: %s - %d turns\n", classroom.players[IDs_winners_crit[0][5]].name, data_crit[IDs_winners_crit[0][5]][0]);
		System.out.printf("7th: %s - %d turns\n", classroom.players[IDs_winners_crit[0][6]].name, data_crit[IDs_winners_crit[0][6]][0]);
		System.out.printf("8th: %s - %d turns\n", classroom.players[IDs_winners_crit[0][7]].name, data_crit[IDs_winners_crit[0][7]][0]);
		System.out.printf("9th: %s - %d turns\n", classroom.players[IDs_winners_crit[0][8]].name, data_crit[IDs_winners_crit[0][8]][0]);
		System.out.printf("10t: %s - %d turns\n\n", classroom.players[IDs_winners_crit[0][9]].name, data_crit[IDs_winners_crit[0][9]][0]);
		
		System.out.printf("Best Survivor (Tot): %s - %d spots\n", classroom.players[IDs_winners_best[1][0]].name, data_best[IDs_winners_best[1][0]][1]);
		System.out.printf("2nd: %s - %d spots\n", classroom.players[IDs_winners_best[1][1]].name, data_best[IDs_winners_best[1][1]][1]);
		System.out.printf("3rd: %s - %d spots\n", classroom.players[IDs_winners_best[1][2]].name, data_best[IDs_winners_best[1][2]][1]);
		System.out.printf("4th: %s - %d spots\n", classroom.players[IDs_winners_best[1][3]].name, data_best[IDs_winners_best[1][3]][1]);
		System.out.printf("5th: %s - %d spots\n", classroom.players[IDs_winners_best[1][4]].name, data_best[IDs_winners_best[1][4]][1]);
		System.out.printf("6th: %s - %d spots\n", classroom.players[IDs_winners_best[1][5]].name, data_best[IDs_winners_best[1][5]][1]);
		System.out.printf("7th: %s - %d spots\n", classroom.players[IDs_winners_best[1][6]].name, data_best[IDs_winners_best[1][6]][1]);
		System.out.printf("8th: %s - %d spots\n", classroom.players[IDs_winners_best[1][7]].name, data_best[IDs_winners_best[1][7]][1]);
		System.out.printf("9th: %s - %d spots\n", classroom.players[IDs_winners_best[1][8]].name, data_best[IDs_winners_best[1][8]][1]);
		System.out.printf("10t: %s - %d spots\n", classroom.players[IDs_winners_best[1][9]].name, data_best[IDs_winners_best[1][9]][1]);
		System.out.printf("Crit.Survivor (Tot): %s - %d spots\n", classroom.players[IDs_winners_crit[1][0]].name, data_crit[IDs_winners_crit[1][0]][1]);
		System.out.printf("2nd: %s - %d spots\n", classroom.players[IDs_winners_crit[1][1]].name, data_crit[IDs_winners_crit[1][1]][1]);
		System.out.printf("3rd: %s - %d spots\n", classroom.players[IDs_winners_crit[1][2]].name, data_crit[IDs_winners_crit[1][2]][1]);
		System.out.printf("4th: %s - %d spots\n", classroom.players[IDs_winners_crit[1][3]].name, data_crit[IDs_winners_crit[1][3]][1]);
		System.out.printf("5th: %s - %d spots\n", classroom.players[IDs_winners_crit[1][4]].name, data_crit[IDs_winners_crit[1][4]][1]);
		System.out.printf("6th: %s - %d spots\n", classroom.players[IDs_winners_crit[1][5]].name, data_crit[IDs_winners_crit[1][5]][1]);
		System.out.printf("7th: %s - %d spots\n", classroom.players[IDs_winners_crit[1][6]].name, data_crit[IDs_winners_crit[1][6]][1]);
		System.out.printf("8th: %s - %d spots\n", classroom.players[IDs_winners_crit[1][7]].name, data_crit[IDs_winners_crit[1][7]][1]);
		System.out.printf("9th: %s - %d spots\n", classroom.players[IDs_winners_crit[1][8]].name, data_crit[IDs_winners_crit[1][8]][1]);
		System.out.printf("10t: %s - %d spots\n\n", classroom.players[IDs_winners_crit[1][9]].name, data_crit[IDs_winners_crit[1][9]][1]);
		
		System.out.printf("Best Corpse   (Max): %s - %d players\n", classroom.players[IDs_winners_best[2][0]].name, data_best[IDs_winners_best[2][0]][2]);
		System.out.printf("2nd: %s - %d players\n", classroom.players[IDs_winners_best[2][1]].name, data_best[IDs_winners_best[2][1]][2]);
		System.out.printf("3rd: %s - %d players\n", classroom.players[IDs_winners_best[2][2]].name, data_best[IDs_winners_best[2][2]][2]);
		System.out.printf("4th: %s - %d players\n", classroom.players[IDs_winners_best[2][3]].name, data_best[IDs_winners_best[2][3]][2]);
		System.out.printf("5th: %s - %d players\n", classroom.players[IDs_winners_best[2][4]].name, data_best[IDs_winners_best[2][4]][2]);
		System.out.printf("6th: %s - %d players\n", classroom.players[IDs_winners_best[2][5]].name, data_best[IDs_winners_best[2][5]][2]);
		System.out.printf("7th: %s - %d players\n", classroom.players[IDs_winners_best[2][6]].name, data_best[IDs_winners_best[2][6]][2]);
		System.out.printf("8th: %s - %d players\n", classroom.players[IDs_winners_best[2][7]].name, data_best[IDs_winners_best[2][7]][2]);
		System.out.printf("9th: %s - %d players\n", classroom.players[IDs_winners_best[2][8]].name, data_best[IDs_winners_best[2][8]][2]);
		System.out.printf("10t: %s - %d players\n", classroom.players[IDs_winners_best[2][9]].name, data_best[IDs_winners_best[2][9]][2]);
		System.out.printf("Crit.Corpse   (Max): %s - %d players\n", classroom.players[IDs_winners_crit[2][0]].name, data_crit[IDs_winners_crit[2][0]][2]);
		System.out.printf("2nd: %s - %d players\n", classroom.players[IDs_winners_crit[2][1]].name, data_crit[IDs_winners_crit[2][1]][2]);
		System.out.printf("3rd: %s - %d players\n", classroom.players[IDs_winners_crit[2][2]].name, data_crit[IDs_winners_crit[2][2]][2]);
		System.out.printf("4th: %s - %d players\n", classroom.players[IDs_winners_crit[2][3]].name, data_crit[IDs_winners_crit[2][3]][2]);
		System.out.printf("5th: %s - %d players\n", classroom.players[IDs_winners_crit[2][4]].name, data_crit[IDs_winners_crit[2][4]][2]);
		System.out.printf("6th: %s - %d players\n", classroom.players[IDs_winners_crit[2][5]].name, data_crit[IDs_winners_crit[2][5]][2]);
		System.out.printf("7th: %s - %d players\n", classroom.players[IDs_winners_crit[2][6]].name, data_crit[IDs_winners_crit[2][6]][2]);
		System.out.printf("8th: %s - %d players\n", classroom.players[IDs_winners_crit[2][7]].name, data_crit[IDs_winners_crit[2][7]][2]);
		System.out.printf("9th: %s - %d players\n", classroom.players[IDs_winners_crit[2][8]].name, data_crit[IDs_winners_crit[2][8]][2]);
		System.out.printf("10t: %s - %d players\n\n", classroom.players[IDs_winners_crit[2][9]].name, data_crit[IDs_winners_crit[2][9]][2]);
		
		System.out.printf("Best Corpse   (Tot): %s - %d points\n", classroom.players[IDs_winners_best[3][0]].name, data_best[IDs_winners_best[3][0]][3]);
		System.out.printf("2nd: %s - %d points\n", classroom.players[IDs_winners_best[3][1]].name, data_best[IDs_winners_best[3][1]][3]);
		System.out.printf("3rd: %s - %d points\n", classroom.players[IDs_winners_best[3][2]].name, data_best[IDs_winners_best[3][2]][3]);
		System.out.printf("4th: %s - %d points\n", classroom.players[IDs_winners_best[3][3]].name, data_best[IDs_winners_best[3][3]][3]);
		System.out.printf("5th: %s - %d points\n", classroom.players[IDs_winners_best[3][4]].name, data_best[IDs_winners_best[3][4]][3]);
		System.out.printf("6th: %s - %d points\n", classroom.players[IDs_winners_best[3][5]].name, data_best[IDs_winners_best[3][5]][3]);
		System.out.printf("7th: %s - %d points\n", classroom.players[IDs_winners_best[3][6]].name, data_best[IDs_winners_best[3][6]][3]);
		System.out.printf("8th: %s - %d points\n", classroom.players[IDs_winners_best[3][7]].name, data_best[IDs_winners_best[3][7]][3]);
		System.out.printf("9th: %s - %d points\n", classroom.players[IDs_winners_best[3][8]].name, data_best[IDs_winners_best[3][8]][3]);
		System.out.printf("10t: %s - %d points\n", classroom.players[IDs_winners_best[3][9]].name, data_best[IDs_winners_best[3][9]][3]);
		System.out.printf("Crit.Corpse   (Tot): %s - %d points\n", classroom.players[IDs_winners_crit[3][0]].name, data_crit[IDs_winners_crit[3][0]][3]);
		System.out.printf("2nd: %s - %d points\n", classroom.players[IDs_winners_crit[3][1]].name, data_crit[IDs_winners_crit[3][1]][3]);
		System.out.printf("3rd: %s - %d points\n", classroom.players[IDs_winners_crit[3][2]].name, data_crit[IDs_winners_crit[3][2]][3]);
		System.out.printf("4th: %s - %d points\n", classroom.players[IDs_winners_crit[3][3]].name, data_crit[IDs_winners_crit[3][3]][3]);
		System.out.printf("5th: %s - %d points\n", classroom.players[IDs_winners_crit[3][4]].name, data_crit[IDs_winners_crit[3][4]][3]);
		System.out.printf("6th: %s - %d points\n", classroom.players[IDs_winners_crit[3][5]].name, data_crit[IDs_winners_crit[3][5]][3]);
		System.out.printf("7th: %s - %d points\n", classroom.players[IDs_winners_crit[3][6]].name, data_crit[IDs_winners_crit[3][6]][3]);
		System.out.printf("8th: %s - %d points\n", classroom.players[IDs_winners_crit[3][7]].name, data_crit[IDs_winners_crit[3][7]][3]);
		System.out.printf("9th: %s - %d points\n", classroom.players[IDs_winners_crit[3][8]].name, data_crit[IDs_winners_crit[3][8]][3]);
		System.out.printf("10t: %s - %d points\n\n", classroom.players[IDs_winners_crit[3][9]].name, data_crit[IDs_winners_crit[3][9]][3]);
		
		System.out.printf("Best Infected (Max): %s - %d kills\n", classroom.players[IDs_winners_best[4][0]].name, data_best[IDs_winners_best[4][0]][4]);
		System.out.printf("2nd: %s - %d kills\n", classroom.players[IDs_winners_best[4][1]].name, data_best[IDs_winners_best[4][1]][4]);
		System.out.printf("3rd: %s - %d kills\n", classroom.players[IDs_winners_best[4][2]].name, data_best[IDs_winners_best[4][2]][4]);
		System.out.printf("4th: %s - %d kills\n", classroom.players[IDs_winners_best[4][3]].name, data_best[IDs_winners_best[4][3]][4]);
		System.out.printf("5th: %s - %d kills\n", classroom.players[IDs_winners_best[4][4]].name, data_best[IDs_winners_best[4][4]][4]);
		System.out.printf("6th: %s - %d kills\n", classroom.players[IDs_winners_best[4][5]].name, data_best[IDs_winners_best[4][5]][4]);
		System.out.printf("7th: %s - %d kills\n", classroom.players[IDs_winners_best[4][6]].name, data_best[IDs_winners_best[4][6]][4]);
		System.out.printf("8th: %s - %d kills\n", classroom.players[IDs_winners_best[4][7]].name, data_best[IDs_winners_best[4][7]][4]);
		System.out.printf("9th: %s - %d kills\n", classroom.players[IDs_winners_best[4][8]].name, data_best[IDs_winners_best[4][8]][4]);
		System.out.printf("10t: %s - %d kills\n", classroom.players[IDs_winners_best[4][9]].name, data_best[IDs_winners_best[4][9]][4]);
		System.out.printf("Crit.Infected (Max): %s - %d kills\n", classroom.players[IDs_winners_crit[4][0]].name, data_crit[IDs_winners_crit[4][0]][4]);
		System.out.printf("2nd: %s - %d kills\n", classroom.players[IDs_winners_crit[4][1]].name, data_crit[IDs_winners_crit[4][1]][4]);
		System.out.printf("3rd: %s - %d kills\n", classroom.players[IDs_winners_crit[4][2]].name, data_crit[IDs_winners_crit[4][2]][4]);
		System.out.printf("4th: %s - %d kills\n", classroom.players[IDs_winners_crit[4][3]].name, data_crit[IDs_winners_crit[4][3]][4]);
		System.out.printf("5th: %s - %d kills\n", classroom.players[IDs_winners_crit[4][4]].name, data_crit[IDs_winners_crit[4][4]][4]);
		System.out.printf("6th: %s - %d kills\n", classroom.players[IDs_winners_crit[4][5]].name, data_crit[IDs_winners_crit[4][5]][4]);
		System.out.printf("7th: %s - %d kills\n", classroom.players[IDs_winners_crit[4][6]].name, data_crit[IDs_winners_crit[4][6]][4]);
		System.out.printf("8th: %s - %d kills\n", classroom.players[IDs_winners_crit[4][7]].name, data_crit[IDs_winners_crit[4][7]][4]);
		System.out.printf("9th: %s - %d kills\n", classroom.players[IDs_winners_crit[4][8]].name, data_crit[IDs_winners_crit[4][8]][4]);
		System.out.printf("10t: %s - %d kills\n\n", classroom.players[IDs_winners_crit[4][9]].name, data_crit[IDs_winners_crit[4][9]][4]);
		
		System.out.printf("Best Infected (Tot): %s - %d points\n", classroom.players[IDs_winners_best[5][0]].name, data_best[IDs_winners_best[5][0]][5]);
		System.out.printf("2nd: %s - %d points\n", classroom.players[IDs_winners_best[5][1]].name, data_best[IDs_winners_best[5][1]][5]);
		System.out.printf("3rd: %s - %d points\n", classroom.players[IDs_winners_best[5][2]].name, data_best[IDs_winners_best[5][2]][5]);
		System.out.printf("4th: %s - %d points\n", classroom.players[IDs_winners_best[5][3]].name, data_best[IDs_winners_best[5][3]][5]);
		System.out.printf("5th: %s - %d points\n", classroom.players[IDs_winners_best[5][4]].name, data_best[IDs_winners_best[5][4]][5]);
		System.out.printf("6th: %s - %d points\n", classroom.players[IDs_winners_best[5][5]].name, data_best[IDs_winners_best[5][5]][5]);
		System.out.printf("7th: %s - %d points\n", classroom.players[IDs_winners_best[5][6]].name, data_best[IDs_winners_best[5][6]][5]);
		System.out.printf("8th: %s - %d points\n", classroom.players[IDs_winners_best[5][7]].name, data_best[IDs_winners_best[5][7]][5]);
		System.out.printf("9th: %s - %d points\n", classroom.players[IDs_winners_best[5][8]].name, data_best[IDs_winners_best[5][8]][5]);
		System.out.printf("10t: %s - %d points\n", classroom.players[IDs_winners_best[5][9]].name, data_best[IDs_winners_best[5][9]][5]);
		System.out.printf("Crit.Infected (Tot): %s - %d points\n", classroom.players[IDs_winners_crit[5][0]].name, data_crit[IDs_winners_crit[5][0]][5]);
		System.out.printf("2nd: %s - %d points\n", classroom.players[IDs_winners_crit[5][1]].name, data_crit[IDs_winners_crit[5][1]][5]);
		System.out.printf("3rd: %s - %d points\n", classroom.players[IDs_winners_crit[5][2]].name, data_crit[IDs_winners_crit[5][2]][5]);
		System.out.printf("4th: %s - %d points\n", classroom.players[IDs_winners_crit[5][3]].name, data_crit[IDs_winners_crit[5][3]][5]);
		System.out.printf("5th: %s - %d points\n", classroom.players[IDs_winners_crit[5][4]].name, data_crit[IDs_winners_crit[5][4]][5]);
		System.out.printf("6th: %s - %d points\n", classroom.players[IDs_winners_crit[5][5]].name, data_crit[IDs_winners_crit[5][5]][5]);
		System.out.printf("7th: %s - %d points\n", classroom.players[IDs_winners_crit[5][6]].name, data_crit[IDs_winners_crit[5][6]][5]);
		System.out.printf("8th: %s - %d points\n", classroom.players[IDs_winners_crit[5][7]].name, data_crit[IDs_winners_crit[5][7]][5]);
		System.out.printf("9th: %s - %d points\n", classroom.players[IDs_winners_crit[5][8]].name, data_crit[IDs_winners_crit[5][8]][5]);
		System.out.printf("10t: %s - %d points\n\n", classroom.players[IDs_winners_crit[5][9]].name, data_crit[IDs_winners_crit[5][9]][5]);
		
		System.out.printf("Best Soul (Freedom): %s - %d attempts\n", classroom.players[IDs_winners_best[6][0]].name, data_best[IDs_winners_best[6][0]][6]);
		System.out.printf("2nd: %s - %d attempts\n", classroom.players[IDs_winners_best[6][1]].name, data_best[IDs_winners_best[6][1]][6]);
		System.out.printf("3rd: %s - %d attempts\n", classroom.players[IDs_winners_best[6][2]].name, data_best[IDs_winners_best[6][2]][6]);
		System.out.printf("4th: %s - %d attempts\n", classroom.players[IDs_winners_best[6][3]].name, data_best[IDs_winners_best[6][3]][6]);
		System.out.printf("5th: %s - %d attempts\n", classroom.players[IDs_winners_best[6][4]].name, data_best[IDs_winners_best[6][4]][6]);
		System.out.printf("6th: %s - %d attempts\n", classroom.players[IDs_winners_best[6][5]].name, data_best[IDs_winners_best[6][5]][6]);
		System.out.printf("7th: %s - %d attempts\n", classroom.players[IDs_winners_best[6][6]].name, data_best[IDs_winners_best[6][6]][6]);
		System.out.printf("8th: %s - %d attempts\n", classroom.players[IDs_winners_best[6][7]].name, data_best[IDs_winners_best[6][7]][6]);
		System.out.printf("9th: %s - %d attempts\n", classroom.players[IDs_winners_best[6][8]].name, data_best[IDs_winners_best[6][8]][6]);
		System.out.printf("10t: %s - %d attempts\n", classroom.players[IDs_winners_best[6][9]].name, data_best[IDs_winners_best[6][9]][6]);
		System.out.printf("Crit.Soul (Freedom): %s - %d attempts\n", classroom.players[IDs_winners_crit[6][0]].name, data_crit[IDs_winners_crit[6][0]][6]);
		System.out.printf("2nd: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][1]].name, data_crit[IDs_winners_crit[6][1]][6]);
		System.out.printf("3rd: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][2]].name, data_crit[IDs_winners_crit[6][2]][6]);
		System.out.printf("4th: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][3]].name, data_crit[IDs_winners_crit[6][3]][6]);
		System.out.printf("5th: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][4]].name, data_crit[IDs_winners_crit[6][4]][6]);
		System.out.printf("6th: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][5]].name, data_crit[IDs_winners_crit[6][5]][6]);
		System.out.printf("7th: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][6]].name, data_crit[IDs_winners_crit[6][6]][6]);
		System.out.printf("8th: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][7]].name, data_crit[IDs_winners_crit[6][7]][6]);
		System.out.printf("9th: %s - %d attempts\n", classroom.players[IDs_winners_crit[6][8]].name, data_crit[IDs_winners_crit[6][8]][6]);
		System.out.printf("10t: %s - %d attempts\n\n", classroom.players[IDs_winners_crit[6][9]].name, data_crit[IDs_winners_crit[6][9]][6]);
		
		System.out.printf("Best Soul (Destruction): %s - %d attempts\n", classroom.players[IDs_winners_best[7][0]].name, data_best[IDs_winners_best[7][0]][7]);
		System.out.printf("2nd: %s - %d attempts\n", classroom.players[IDs_winners_best[7][1]].name, data_best[IDs_winners_best[7][1]][7]);
		System.out.printf("3rd: %s - %d attempts\n", classroom.players[IDs_winners_best[7][2]].name, data_best[IDs_winners_best[7][2]][7]);
		System.out.printf("4th: %s - %d attempts\n", classroom.players[IDs_winners_best[7][3]].name, data_best[IDs_winners_best[7][3]][7]);
		System.out.printf("5th: %s - %d attempts\n", classroom.players[IDs_winners_best[7][4]].name, data_best[IDs_winners_best[7][4]][7]);
		System.out.printf("6th: %s - %d attempts\n", classroom.players[IDs_winners_best[7][5]].name, data_best[IDs_winners_best[7][5]][7]);
		System.out.printf("7th: %s - %d attempts\n", classroom.players[IDs_winners_best[7][6]].name, data_best[IDs_winners_best[7][6]][7]);
		System.out.printf("8th: %s - %d attempts\n", classroom.players[IDs_winners_best[7][7]].name, data_best[IDs_winners_best[7][7]][7]);
		System.out.printf("9th: %s - %d attempts\n", classroom.players[IDs_winners_best[7][8]].name, data_best[IDs_winners_best[7][8]][7]);
		System.out.printf("10t: %s - %d attempts\n", classroom.players[IDs_winners_best[7][9]].name, data_best[IDs_winners_best[7][9]][7]);
		System.out.printf("Crit.Soul (Destruction): %s - %d attempts\n", classroom.players[IDs_winners_crit[7][0]].name, data_crit[IDs_winners_crit[7][0]][7]);
		System.out.printf("2nd: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][1]].name, data_crit[IDs_winners_crit[7][1]][7]);
		System.out.printf("3rd: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][2]].name, data_crit[IDs_winners_crit[7][2]][7]);
		System.out.printf("4th: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][3]].name, data_crit[IDs_winners_crit[7][3]][7]);
		System.out.printf("5th: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][4]].name, data_crit[IDs_winners_crit[7][4]][7]);
		System.out.printf("6th: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][5]].name, data_crit[IDs_winners_crit[7][5]][7]);
		System.out.printf("7th: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][6]].name, data_crit[IDs_winners_crit[7][6]][7]);
		System.out.printf("8th: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][7]].name, data_crit[IDs_winners_crit[7][7]][7]);
		System.out.printf("9th: %s - %d attempts\n", classroom.players[IDs_winners_crit[7][8]].name, data_crit[IDs_winners_crit[7][8]][7]);
		System.out.printf("10t: %s - %d attempts\n\n", classroom.players[IDs_winners_crit[7][9]].name, data_crit[IDs_winners_crit[7][9]][7]);
		
		System.out.printf("Best Player of L4G: %s - %d points\n", classroom.players[IDs_winners_best[8][0]].name, data_best[IDs_winners_best[8][0]][8]);
		System.out.printf("2nd: %s - %d points\n", classroom.players[IDs_winners_best[8][1]].name, data_best[IDs_winners_best[8][1]][8]);
		System.out.printf("3rd: %s - %d points\n", classroom.players[IDs_winners_best[8][2]].name, data_best[IDs_winners_best[8][2]][8]);
		System.out.printf("4th: %s - %d points\n", classroom.players[IDs_winners_best[8][3]].name, data_best[IDs_winners_best[8][3]][8]);
		System.out.printf("5th: %s - %d points\n", classroom.players[IDs_winners_best[8][4]].name, data_best[IDs_winners_best[8][4]][8]);
		System.out.printf("6th: %s - %d points\n", classroom.players[IDs_winners_best[8][5]].name, data_best[IDs_winners_best[8][5]][8]);
		System.out.printf("7th: %s - %d points\n", classroom.players[IDs_winners_best[8][6]].name, data_best[IDs_winners_best[8][6]][8]);
		System.out.printf("8th: %s - %d points\n", classroom.players[IDs_winners_best[8][7]].name, data_best[IDs_winners_best[8][7]][8]);
		System.out.printf("9th: %s - %d points\n", classroom.players[IDs_winners_best[8][8]].name, data_best[IDs_winners_best[8][8]][8]);
		System.out.printf("10t: %s - %d points\n", classroom.players[IDs_winners_best[8][9]].name, data_best[IDs_winners_best[8][9]][8]);
		System.out.printf("Crit.Player of L4G: %s - %d points\n", classroom.players[IDs_winners_crit[8][0]].name, data_crit[IDs_winners_crit[8][0]][8]);
		System.out.printf("2nd: %s - %d points\n", classroom.players[IDs_winners_crit[8][1]].name, data_crit[IDs_winners_crit[8][1]][8]);
		System.out.printf("3rd: %s - %d points\n", classroom.players[IDs_winners_crit[8][2]].name, data_crit[IDs_winners_crit[8][2]][8]);
		System.out.printf("4th: %s - %d points\n", classroom.players[IDs_winners_crit[8][3]].name, data_crit[IDs_winners_crit[8][3]][8]);
		System.out.printf("5th: %s - %d points\n", classroom.players[IDs_winners_crit[8][4]].name, data_crit[IDs_winners_crit[8][4]][8]);
		System.out.printf("6th: %s - %d points\n", classroom.players[IDs_winners_crit[8][5]].name, data_crit[IDs_winners_crit[8][5]][8]);
		System.out.printf("7th: %s - %d points\n", classroom.players[IDs_winners_crit[8][6]].name, data_crit[IDs_winners_crit[8][6]][8]);
		System.out.printf("8th: %s - %d points\n", classroom.players[IDs_winners_crit[8][7]].name, data_crit[IDs_winners_crit[8][7]][8]);
		System.out.printf("9th: %s - %d points\n", classroom.players[IDs_winners_crit[8][8]].name, data_crit[IDs_winners_crit[8][8]][8]);
		System.out.printf("10t: %s - %d points\n\n", classroom.players[IDs_winners_crit[8][9]].name, data_crit[IDs_winners_crit[8][9]][8]);
	}

	public void PrintResultsOf(int ID, Classroom classroom)
	{
		System.out.printf("----- Results of %s -----\n", classroom.players[ID].name);
		
		System.out.printf("Best Survivor (Max): %d turns (%d)\n", data_best[0][0], data_best[0][0] - data_best[IDs_winners_best[0][0]][0]);
		System.out.printf("Crit.Survivor (Max): %d turns (%d)\n\n", data_crit[0][0], data_crit[0][0] - data_crit[IDs_winners_crit[0][0]][0]);
		
		System.out.printf("Best Survivor (Tot): %d spots (%d)\n", data_best[0][1], data_best[0][1] - data_best[IDs_winners_best[1][0]][1]);
		System.out.printf("Crit.Survivor (Tot): %d spots (%d)\n\n", data_crit[0][1], data_crit[0][1] - data_crit[IDs_winners_crit[1][0]][1]);
		
		System.out.printf("Best Corpse   (Max): %d players (%d)\n", data_best[0][2], data_best[0][2] - data_best[IDs_winners_best[2][0]][2]);
		System.out.printf("Crit.Corpse   (Max): %d players (%d)\n\n", data_crit[0][2], data_crit[0][2] - data_crit[IDs_winners_crit[2][0]][2]);
		
		System.out.printf("Best Corpse   (Tot): %d points (%d)\n", data_best[0][3], data_best[0][3] - data_best[IDs_winners_best[3][0]][3]);
		System.out.printf("Crit.Corpse   (Tot): %d points (%d)\n\n", data_crit[0][3], data_crit[0][3] - data_crit[IDs_winners_crit[3][0]][3]);
		
		System.out.printf("Best Infected (Max): %d kills (%d)\n", data_best[0][4], data_best[0][4] - data_best[IDs_winners_best[4][0]][4]);
		System.out.printf("Crit.Infected (Max): %d kills (%d)\n\n", data_crit[0][4], data_crit[0][4] - data_crit[IDs_winners_crit[4][0]][4]);
		
		System.out.printf("Best Infected (Tot): %d points (%d)\n", data_best[0][5], data_best[0][5] - data_best[IDs_winners_best[5][0]][5]);
		System.out.printf("Crit.Infected (Tot): %d points (%d)\n\n", data_crit[0][5], data_crit[0][5] - data_crit[IDs_winners_crit[5][0]][5]);
		
		System.out.printf("Best Soul (Freedom): %d attempts (%d)\n", data_best[0][6], data_best[0][6] - data_best[IDs_winners_best[6][0]][6]);
		System.out.printf("Crit.Soul (Freedom): %d attempts (%d)\n\n", data_crit[0][6], data_crit[0][6] - data_crit[IDs_winners_crit[6][0]][6]);
		
		System.out.printf("Best Soul (Destruction): %d attempts (%d)\n", data_best[0][7], data_best[0][7] - data_best[IDs_winners_best[7][0]][7]);
		System.out.printf("Crit.Soul (Destruction): %d attempts (%d)\n\n", data_crit[0][7], data_crit[0][7] - data_crit[IDs_winners_crit[7][0]][7]);
		
		System.out.printf("Best Final Grade: %d points (%d)\n", data_best[0][8], data_best[0][8] - data_best[IDs_winners_best[8][0]][8]);
		System.out.printf("Crit.Final Grade: %d points (%d)\n\n", data_crit[0][8], data_crit[0][8] - data_crit[IDs_winners_crit[8][0]][8]);
		
		System.out.printf("My Critical Game Number: %d\n", criticalGameNumbers[ID]);
	}
	
	public void PrintBestFinalGrades(Classroom classroom)
	{
		System.out.println("Best Final Grades:");
		System.out.println("  grade (  char_E) - name");
		
		for ( int iPlayer = 0; iPlayer < Constants.Total_Players; iPlayer++ )
		{
			System.out.printf("%7d (%8d) - %s\n", data_best[iPlayer][8], data_best[iPlayer][8] - data_best[IDs_winners_best[8][0]][8], classroom.players[iPlayer].name);
		}
	}
	
	public void SaveToFile(String fileName)
	{
		try
		{
			PrintStream ws = new PrintStream(fileName);
			
			for ( long[] rows : data_best )
				for ( long value : rows )
					ws.println(value);
			
			for ( long[] rows : data_crit )
				for ( long value : rows )
					ws.println(value);
			
			for ( int[] rows : IDs_winners_best )
				for ( int value : rows )
					ws.println(value);
			
			for ( int[] rows : IDs_winners_crit )
				for ( int value : rows )
					ws.println(value);
			
			for ( long value : criticalGameNumbers )
				ws.println(value);
			
			ws.flush();
			ws.close();
		}
		catch ( IOException e )
		{
			e.printStackTrace();
		}
	}
	
	public void SaveToCSV(String fileName)
	{
		try
		{
			PrintStream ws = new PrintStream(fileName);
			
			ws.println(
					"ID,B_SMax,B_STot,B_CMax,B_CTot,B_IMax,B_ITot,B_F,B_D,B_G," +
					"C_SMax,C_STot,C_CMax,C_CTot,C_IMax,C_ITot,C_F,C_D,C_G");

			for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
			{
				ws.printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%n", 
						iPlayer,
						data_best[iPlayer][Classroom.Score_Survivor_Max],
						data_best[iPlayer][Classroom.Score_Survivor_Total],
						data_best[iPlayer][Classroom.Score_Corpse_Max],
						data_best[iPlayer][Classroom.Score_Corpse_Total],
						data_best[iPlayer][Classroom.Score_Infected_Max],
						data_best[iPlayer][Classroom.Score_Infected_Total],
						data_best[iPlayer][Classroom.Score_Soul_Freedom],
						data_best[iPlayer][Classroom.Score_Soul_Destruction],
						data_best[iPlayer][Classroom.Score_Titles],
						data_crit[iPlayer][Classroom.Score_Survivor_Max],
						data_crit[iPlayer][Classroom.Score_Survivor_Total],
						data_crit[iPlayer][Classroom.Score_Corpse_Max],
						data_crit[iPlayer][Classroom.Score_Corpse_Total],
						data_crit[iPlayer][Classroom.Score_Infected_Max],
						data_crit[iPlayer][Classroom.Score_Infected_Total],
						data_crit[iPlayer][Classroom.Score_Soul_Freedom],
						data_crit[iPlayer][Classroom.Score_Soul_Destruction],
						data_crit[iPlayer][Classroom.Score_Titles]);
			}
			
			ws.flush();
			ws.close();
		}
		catch ( IOException e )
		{
			e.printStackTrace();
		}
	}
	
	public boolean LoadFromFile(String fileName)
	{
		try
		{
			InputStream rs = new FileInputStream(fileName);
			Scanner scanner = new Scanner(rs);
			
			for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
				for ( int iTitle = 0; iTitle < Classroom.Score_Titles + 1; ++iTitle )
					data_best[iPlayer][iTitle] = scanner.nextLong();
			
			for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
				for ( int iTitle = 0; iTitle < Classroom.Score_Titles + 1; ++iTitle )
					data_crit[iPlayer][iTitle] = scanner.nextLong();
			
			for ( int iTitle = 0; iTitle < Classroom.Score_Titles + 1; ++iTitle )
				for ( int iRank = 0; iRank < 10; ++iRank )
					IDs_winners_best[iTitle][iRank] = scanner.nextInt();

			for ( int iTitle = 0; iTitle < Classroom.Score_Titles + 1; ++iTitle )
				for ( int iRank = 0; iRank < 10; ++iRank )
					IDs_winners_crit[iTitle][iRank] = scanner.nextInt();
			
			for ( int iPlayer = 0; iPlayer < Constants.Total_Players; ++iPlayer )
				criticalGameNumbers[iPlayer] = scanner.nextLong();

			scanner.close();
		}
		catch ( IOException e )
		{
			return false;
		}
		
		return true;
	}
}
