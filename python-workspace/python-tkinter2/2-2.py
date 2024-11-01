"""


아래 코드와 주석을 참고하여 이곳에 필요한 함수를 작성하여
채점과제02-2 예시화면처럼 실행되도록 만들어주세요.
본인 작성한 코드와 결과화면이 함께 보이도록 캡쳐하여 이미지 파일을 만들고
이를 작성한 파이썬 코드와 함께 제출합니다.


"""

def find_location(value_List, value): # 숫자의 위치를 찾는 함수
    for i in range(len(value_List)): # 0부터 value_List 리스트의 길이만큼 반복
        if value == value_List[i]: # i번째 value_List값과 value가 같으면
            return i # 해당 인덱스 i 반환
    return -1 # 반복문이 끝나도 찾지 못한 경우 -1 반환


value_List = [17, 92, 18, 33, 58, 7, 33, 42]            #value_List 생성

value = int(input("찾고자 하는 숫자가 무엇인가요? "))   #찾고자 하는 숫자 입력받아 변수 value에 대입(저장)

result = find_location(value_List, value)               #find_location 함수 호출 및 반환값 result에 대입(저장)

if result == -1:                                        #reuslt값이 -1와 같으면
    print("찾고자 하는 숫자는 리스트에 없습니다.")      #찾고자 하는 숫자가 없다는 문구 출력
else:                                                   #result값이 -1와 같지 않으면
    print("찾고자 하는 숫자는 리스트 Index %d에 있습니다."%result) #찾고자 하는 숫자가 있는 위치 문구 출력

