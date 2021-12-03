################################################################################
# tsp_lab.py Version 2021.11.21v1
################################################################################

import turtle
import math, random
import time, threading
import requests
import os.path 
import sys


################################################################################
# IMPORTANT: 자신의 정보로 수정해주세요!
################################################################################

# 닉네임
NICKNAME = 'Shark'

# Auth Code (https://esohn.be/register 에서 Auth Code 복사)
AUTH_CODE = 'c6b60a9f96342e29e8c9ee8e3bd6de66'

################################################################################

class TSP:

    # -------------------------------------------------------------------------------------------
    # 초기화 코드
    def __init__(self, nickname, auth_code):

        # Auth Code 확인
        if not AUTH_CODE:
            print('Auth Code를 수정해주세요. (https://esohn.be/register 에서 Auth Code 복사)')
            sys.exit()

        # TSP Helper 다운로드
        if not os.path.isfile('tsp_helper.py'):
            self.download_tsp_helper()
        
        import tsp_helper

        # TSP Helper object
        self.helper = tsp_helper.TSP_Helper( self, nickname, auth_code )

        print( '\n\n{0}  TSP Helper Version: {1}  {0}\n\n'.format( '-'*10, self.helper.TSP_HELPER_VERSION) )

        # a tutle for drawing nodes
        self.turtle_node = turtle.Turtle()
        self.turtle_node.shape('circle')
        self.turtle_node.color('navy')
        self.turtle_node.shapesize(0.4)
        self.turtle_node.penup()
        self.turtle_node.ht()

        # a tutle for drawing paths
        self.turtle_path = turtle.Turtle()
        self.turtle_path.color('green')
        self.turtle_path.ht()

        # ready to run loop
        self.helper.start_loop()

    # -------------------------------------------------------------------------------------------
    # Random Algorithm - 문제 (1)
    # -------------------------------------------------------------------------------------------
    def make_random_path(self):

        # ----------------- DO NOT EDIT ------------------
        self.helper.before_making_path('Random Algorithm')
        # ------------------------------------------------

        # 전체 도시 수 = len(self.helper.nodes)
        # 새로 만들어질 경로: path_edit
        # 모든 도시를 경유하는 path 생성
        # Edit this (1)
        path_edit = []

        # path_edit를 섞음 (shuffle)
        # Edit this (2)
        random.shuffle(path_edit)
        
        # 처음 도시로 다시 돌아오기 (path_edit의 첫 엘리먼트를 맨 뒤에 append)
        # Edit this (3)
        path_edit.append(path_edit[0])

        # ----------------- DO NOT EDIT ------------------
        self.helper.after_making_path( path_edit )
        # ------------------------------------------------


    # -------------------------------------------------------------------------------------------
    # Greedy Algorithm - 문제 (2)
    # -------------------------------------------------------------------------------------------
    def make_greedy_path(self):

        # ----------------- DO NOT EDIT ------------------
        self.helper.before_making_path('Greedy Algorithm')
        # ------------------------------------------------

        # 모든 도시를 가지고 있는 pool 리스트 생성
        pool = list(range(len(self.helper.nodes)))

        # 새로 만들어질 경로: path_edit
        path_edit = []
        
        # 첫 도시를 pool에서 pop하여 path_edit에 추가
        # 첫 도시를 선택하는 기준은 본인이 원하는 대로 
        path_edit.append( pool.pop( 0 ) )

        # 만약 pool에 도시가 하나라도 남아있다면
        while len( pool ) > 0:

            # min_index: 현재 도시(path_edit[-1])와 pool에 있는 도시 중 최소 거리를 가진, 도시의 index (pool 안에서의 index)
            # min_dist: 현재 도시(path_edit[-1])와 pool에 있는 도시 중 최소 거리를 저장
            #   * 예를 들어 pool 안에서 index 2를 가진 도시와의 거리가 15.0이고 그 도시가 현재 도시(path_edit[-1]) 에서 제일 가깝다면,
            #   아래의 반복이 끝난 후 min_index = 2, min_dist = 15.0 이 저장되어 있을 것
            min_index = None
            min_dist = None

            # pool 안에 있는 모든 도시들에 대하여
            for pool_i in range(len(pool)):
                
                # 현재 도시 (가장 최근에 path_edit에 추가된 도시)를 node1에 대입
                # Edit this (1)
                node1 = path_edit.pop(len(path_edit))

                # pool 리스트 안의 pool_i 인덱스에 있는 도시를 node2에 대입
                # Edit this (2)
                node2 = pool[pool_i]

                # 두 도시의 거리 dist를 계산 ( self.helper.get_dist( a, b )를 사용하여 거리를 구할 수 있음 )
                # Edit this (3)
                dist = self.helper.get_dist(node1, node2)

                # 만약 dist가 기존의 min_dist보다 짧거나 min_dist가 아직 None이라면
                # Edit this (4)
                if min_dist is None or min_dist > dist:
                    # min_dist에는 dist를 대입
                    # Edit this (5)
                    min_dist = dist

                    # min_index에는 현재 pool의 index인 pool_i를 대입
                    # Edit this (6)
                    min_index = pool_i

            # min_index와 min_dist를 구했으니
            # pool에서 min_index 도시를 pop() 해서 path_edit에 append
            # Edit this (7)
            path_edit.append( pool.pop(min_index) )


        # 모든 도시를 다 방문했으니 처음 도시로 돌아옴 (path_edit의 첫 엘리먼트를 맨 뒤에 append)
        path_edit.append( path_edit[0] )


        # ----------------- DO NOT EDIT ------------------
        self.helper.after_making_path( path_edit )
        # ------------------------------------------------


    # -------------------------------------------------------------------------------------------
    # 2-Opt Algorithm - 문제 (3)
    # -------------------------------------------------------------------------------------------
    def make_2opt_path(self):

        # ------------------------------------------------
        # 만약 완성된 경로가 아직 없다면 랜덤이나 그리디로 시작
        if len( self.helper.path ) == 0:
            self.make_random_path() # Editable
            # self.make_greedy_path() # Editable

        # ----------------- DO NOT EDIT ------------------
        self.helper.before_making_path('2-Opt Algorithm' )
        # ------------------------------------------------

        # path_edit 경로에 완성된 경로를 복사
        # 이후 path_edit를 수정
        path_edit = self.helper.path.copy()

        # 반복하며 경로를 수정
        # 얼마나 반복할지는 원하는 대로 Edit this (1)
        iteration_num = 10000

        for trial in range(iteration_num):

            # 경로를 슬라이싱하기 위한 범위 지정
            # 슬라이드의 설명 참조
            i = 0 # Edit this (2)
            k = 1 # Edit this (3)

            # 현재의 경로 path_edit를 3 조각으로 slicing (path1, path2, path3)
            path1 = [] # Edit this (4)
            path2 = [] # Edit this (5)
            path3 = [] # Edit this (6)

            # path2만 거꾸로 하여 다시 이어붙임 ( path1 + path2* + path3 )
            path_new = path1 + list(reversed(path2)) + path3

            # 만약 새로 만들어진 경로 path_new의 총 길이가 기존의 path_edit의 총 길이보다 줄어들었다면
            # 경로의 총 길이를 구하기 위해서는 self.helper.get_path_length()를 사용
            if 0 < self.helper.get_path_length(path_edit): # Edit this (7)
                # path_new를 path_edit으로
                path_edit = path_new.copy()

            # -------------- DO NOT EDIT ------------------------
            # 반복 도중 주기적으로 서버에 반영하는 부분
            # progress bar (0~100) 값을 update , trial: 현재 반복 수 , iteration_num: 전체 반복 수
            if trial % 100 == 0:
                self.helper.during_making_path( path_edit, trial, iteration_num )
            # ------------------------------------------------

        # ----------------- DO NOT EDIT ------------------
        self.helper.after_making_path( path_edit )
        # ------------------------------------------------


    # -------------------------------------------------------------------------------------------
    # Your Own Algorithm - 자신만의 변형된 알고리즘을 시도하는 경우 간단히 기술. 
    #                      기술된 내용에 따라 보너스 점수 있음
    # -------------------------------------------------------------------------------------------
    # - 어떤 방법인지에 대한 설명:
    #
    #
    # - 2opt와의 성능상 차이에 대한 분석:
    #
    #
    # - 시행착오를 통해 배운점:
    #
    #
    def make_yourown_path(self):

        # ------------------------------------------------
        # 만약 완성된 경로가 아직 없다면 랜덤이나 그리디로 시작
        if len( self.helper.path ) == 0:
            self.make_random_path()

        # ------------------------------------------------
        self.helper.before_making_path('Your Own Algorithm')
        # ------------------------------------------------

        # path_edit 경로에 완성된 경로를 복사
        # 이후 path_edit를 수정
        path_edit = self.helper.path.copy()

        # 반복하며 경로를 수정 
        iteration_num = 5000 # 얼마나 반복할지는 원하는 대로 Edit this (1)

        for trial in range(iteration_num):


            #
            # path_edit을 수정하는 부분
            #




            # -------------- DO NOT EDIT ------------------------
            # 반복 도중 주기적으로 서버에 반영하는 부분
            # progress bar (0~100) 값을 update , trial: 현재 반복 수 , iteration_num: 전체 반복 수
            if trial % 100 == 0:
                self.helper.during_making_path( path_edit, trial, iteration_num )
            # ------------------------------------------------

        # ----------------- DO NOT EDIT ------------------
        self.helper.after_making_path( path_edit )
        # ------------------------------------------------

    # -------------------------------------------------------------------------------------------
    # 도시와 경로를 그림
    def draw(self):
        
        # 기존 그림 클리어
        self.turtle_node.clear()
        self.turtle_path.clear()

        # 모든 도시의 위치에 stamp
        for node in self.helper.nodes:
            self.turtle_node.setposition( node[1], node[2] )
            self.turtle_node.color('black')
            self.turtle_node.stamp()
            self.turtle_node.color('blue')

        is_first = True
        # 경로를 따라 직선 그리기
        for index in self.helper.path:
            node = self.helper.nodes[index]

            if is_first:
                self.turtle_path.penup()
                is_first = False
            else:
                self.turtle_path.pendown()

            self.turtle_path.setposition( node[1], node[2] )


    # -------------------------------------------------------------------------------------------
    # TSP Helper download - DO NOT EDIT
    def download_tsp_helper(self):

        TSP_HELPER_URL = 'https://s3.ap-northeast-2.amazonaws.com/esohn.be/python/tsp_helper.py'
        
        r = requests.get(TSP_HELPER_URL, allow_redirects=True)
       
        if r.status_code == 200:
            with open('tsp_helper.py', 'wb') as f:
                f.write( r.content )
        else:
            print('ERROR: unable to download tsp_helper.py!')



if __name__ == "__main__":

    # -------------------------------------------------------------------------------------------
    # Create a TSP object

    tsp = TSP( NICKNAME, AUTH_CODE )


