from settings import *
import random, sys

class ObjectController:
    # 플레이어 관련 객체 및 ID 집합
    __player_id = set()
    __player_object = dict()
    __player_missile_ids = set()
    __player_missile_objects = dict()

    # 적 관련 객체 및 ID 집합
    __enemy_ids = set()
    __enemy_objects = dict()
    __enemy_missile_ids = set()
    __enemy_missile_objects = dict()

    # 효과 관련 객체 및 ID 집합
    __effect_ids = set()
    __effect_objects = dict()

    @classmethod
    def reset(cls):
        # 모든 객체 및 ID 초기화
        __player_id = set()
        __player_object = dict()
        __player_missile_ids = set()
        __player_missile_objects = dict()

        __enemy_ids = set()
        __enemy_objects = dict()
        __enemy_missile_ids = set()
        __enemy_missile_objects = dict()

        __effect_ids = set()
        __effect_objects = dict()

    @classmethod
    def getPlayerObjects(cls):
        # 플레이어 객체 및 미사일 객체 반환
        return cls.__player_object, cls.__player_missile_objects

    @classmethod
    def getEnemyObjects(cls):
        # 적 객체 및 미사일 객체 반환
        return cls.__enemy_objects, cls.__enemy_missile_objects

    @classmethod
    def getEffectObjects(cls):
        # 효과 객체 반환
        return cls.__effect_objects

    @classmethod
    def __init_effect_objects(cls):
        # 효과 객체 초기화
        cls.__effect_ids = set()
        cls.__effect_objects = dict()

    @classmethod
    def enroll(cls, my_object):
        # 객체 등록
        if my_object.team == 'enemy':
            if my_object.role == 'missile':
                # 적 미사일 객체 등록
                object_id = cls.__issueID(cls.__enemy_missile_ids)
                cls.__enemy_missile_objects[object_id] = my_object
            elif my_object.role == 'fighter-plane':
                # 적 전투기 객체 등록
                object_id = cls.__issueID(cls.__enemy_ids)
                cls.__enemy_objects[object_id] = my_object

        elif my_object.team == 'player':
            if my_object.role == 'missile':
                # 플레이어 미사일 객체 등록
                object_id = cls.__issueID(cls.__player_missile_ids)
                cls.__player_missile_objects[object_id] = my_object
            elif my_object.role == 'fighter-plane':
                # 플레이어 전투기 객체 등록
                object_id = cls.__issueID(cls.__player_id)
                cls.__player_object[object_id] = my_object

        elif my_object.team == 'none':
            if my_object.role == 'effect':
                # 효과 객체 등록
                object_id = cls.__issueID(cls.__effect_ids)
                cls.__effect_objects[object_id] = my_object

        return object_id

    @classmethod
    def __issueID(cls, id_set):
        # 고유 ID 발급
        while True:
            new_id = random.randrange(sys.maxsize)
            if new_id in id_set:
                continue
            else:
                id_set.add(new_id)
                return new_id

    @classmethod
    def __colision(cls, object1, object2):
        # 두 객체의 충돌 여부 판단
        if max(0, min(object1[2], object2[2]) - max(object1[0], object2[0])) * max(0, min(object1[3], object2[3]) - max(
                object1[1], object2[1])) > 0:
            return True

    @classmethod
    def __remove_objects(cls, object1_ids, objects1, object2_ids=None, objects2=None, criterion='screen-out'):
        # 객체 제거 조건에 따라 처리
        if criterion == 'screen-out':
            # 화면 밖으로 나간 객체 제거
            while True:
                flag = True
                for object1_id in object1_ids:
                    object1 = objects1[object1_id]

                    x, y = object1.obj_coord
                    if x < 0 or x >= SCREEN_WIDTH or y < 0 or y >= SCREEN_HEIGHT:
                        flag = False
                        break
                if flag == False:
                    object1_ids.remove(object1_id)
                    del objects1[object1_id]
                else:
                    break

        elif criterion == 'iou':
            # 충돌한 객체 제거
            while True:
                flag = True
                for object1_id in object1_ids:
                    object1 = objects1[object1_id]
                    for object2_id in object2_ids:
                        object2 = objects2[object2_id]
                        if cls.__colision(object1.image_coord, object2.image_coord):
                            flag = False
                            break
                    if flag == False:
                        if object1.role == 'fighter-plane' and object2.role == 'missile':
                            # 전투기와 미사일 충돌 처리
                            object1._be_attacked(object2)
                            if object1.hp <= 0:
                                object1_ids.remove(object1_id)
                                del objects1[object1_id]
                                if object1.team == 'enemy' and object2.team == 'player':
                                    if cls.__player_id:
                                        player_id = list(cls.__player_id)[0]
                                        cls.__player_object[player_id]._add_kill_point()

                            object2_ids.remove(object2_id)
                            del objects2[object2_id]
                        elif object1.role == 'missile' and object2.role == 'missile':
                            # 미사일끼리 충돌 처리
                            object1_ids.remove(object1_id)
                            object2_ids.remove(object2_id)
                            del objects1[object1_id]
                            del objects2[object2_id]
                        break
                if flag: break

    @classmethod
    def renew(cls):
        # 객체 갱신
        cls.__init_effect_objects()

        for enemy_id in cls.__enemy_ids:
            enemy_object = cls.__enemy_objects[enemy_id]
            enemy_object.shoot()

        for player_missile_id in cls.__player_missile_ids:
            player_missile_object = cls.__player_missile_objects[player_missile_id]
            player_missile_object.move()

        for enemy_id in cls.__enemy_ids:
            enemy_object = cls.__enemy_objects[enemy_id]
            enemy_object.move()

        for enemy_missile_id in cls.__enemy_missile_ids:
            enemy_missile_object = cls.__enemy_missile_objects[enemy_missile_id]
            enemy_missile_object.move()

        # 화면 밖으로 나간 객체 제거
        cls.__remove_objects(cls.__player_missile_ids, cls.__player_missile_objects)
        cls.__remove_objects(cls.__enemy_ids, cls.__enemy_objects)
        cls.__remove_objects(cls.__enemy_missile_ids, cls.__enemy_missile_objects)

        # 충돌로 인한 객체 제거
        cls.__remove_objects(cls.__player_id, cls.__player_object, cls.__enemy_missile_ids, cls.__enemy_missile_objects,
                             'iou')
        cls.__remove_objects(cls.__player_missile_ids, cls.__player_missile_objects, cls.__enemy_missile_ids,
                             cls.__enemy_missile_objects, 'iou')
        cls.__remove_objects(cls.__enemy_ids, cls.__enemy_objects, cls.__player_missile_ids,
                             cls.__player_missile_objects, 'iou')
