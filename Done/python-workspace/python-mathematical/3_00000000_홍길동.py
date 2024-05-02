# 문제에서 주어진 변수 선언
load_list = []
displacement_list = []
stress_list = []
strain_list = []
a = (0.05 / 2) ** 2 * 3.141592
h = 0.1


# 하위 문제 1번
def prob3_1():
    # 데이터 파일을 불러옴
    f = open("prob_3_data.csv")

    # 첫재 줄은 읽지 않기 위해 헤더 판별 boolean 변수 선언 후 참으로 초기화
    header = True
    # 파일을 한줄씩 읽음
    for line in f:
        # 첫줄은 헤더이며, 읽었으므로
        if header:
            # 헤더에 거짓 대입 후
            header = False
            # 다음 줄부터 반복
            continue
        # 각 라인을 ','로 쪼개어 변위와 하중에 각각 저장
        displacement, load = line.split(",")
        # 저장된 변수는 문자열이므로 실수형으로 형변환하여 리스트에 저장
        load_list.append(float(load))
        # 마찬가지로 정제 후 단위를 맞추기 위해 1000으로 나누어 저장
        displacement_list.append(float(displacement) / 1000)

    # 파일 종료
    f.close()


# 하위 문제 2번
def prob3_2():
    # 하중 리스트의 각 하중을 차례로 불러옴
    for load in load_list:
        # 하중을 단면적 A로 나눈 값을 응력 리스트에 차례대로 저장
        stress_list.append(load / a)
    # 뱐위 리스트의 각 하중을 차례로 불러옴
    for displacement in displacement_list:
        # 변위를 높이 h로 나눈 값을 변형률 리스트에 차례대로 저장
        strain_list.append(displacement / h)


# 하위 문제 3번
def prob3_3():
    # 내장 함수 max를 사용하여 응력의 최댓값을 찾아냄
    ucs_stress = max(stress_list)

    # 리스트를 차례로 순회
    for i in range(len(stress_list)):
        # 현재 인덱스의 응률이 최댓값이면
        if stress_list[i] == ucs_stress:
            # 같은 인덱스의 변형률을 저장
            ucs_strain = strain_list[i]

    # 탄성계수 계산
    ucs_youngs = ucs_stress / ucs_strain

    # 최대 응률, 최대 변형률, 탄성계수 반환
    return ucs_stress, ucs_strain, ucs_youngs


# 하위 문제 4번
def prob3_4():
    # 저장할 파일 이름 지정
    filename = "prob_3_4_00000000_홍길동.csv"

    # 파일을 쓰기 전용으로 생성
    f = open(filename, "w")
    # 헤더 작성
    f.write("Displacement(m),Load(kN),Stress(kPa),Strain\n")

    # 리스트를 순회하며
    for i in range(len(displacement_list)):
        # 변위, 하중, 응률, 변형률 작성
        f.write(
            str(displacement_list[i]) + "," + str(load_list[i]) + "," + str(stress_list[i]) + "," + str(
                strain_list[i]) + "\n")

    # 파일을 저장하고 닫음
    f.close()

    # 파일 이름 반환
    return filename


# 출력부
print("3.1 result\n")
prob3_1()
print("Load(kN) : " + str(load_list[:10]) + "\n")
print("Displacement(m) : " + str(displacement_list[:10]) + "\n")

print("3.2 result\n")
prob3_2()
print("Stress(kPa) : " + str(stress_list[:10]) + "\n")
print("Strain : " + str(strain_list[:10]) + "\n")

print("3.3 result\n")
result = prob3_3()
print("ucs(MPa) : " + str(result[0] / 1000) + "\n")
print("ucs_strain : " + str(result[1]) + "\n")
print("ucs_youngs(GPa) : " + str(result[2] / 1000000) + "\n")

print("3.4 result\n")
print(prob3_4() + " is created")
