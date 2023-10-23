package com.teamproject.hamster.controller;

import com.teamproject.hamster.dto.ProductDTO;
import com.teamproject.hamster.view.ListView;

import java.util.ArrayList;
import java.util.Scanner;

public class SelectListController {
    private ArrayList<ProductDTO> selectList = new ArrayList<>();
    private Scanner sc = new Scanner(System.in);
    public void selectMenu() {
        int productNumber = 0;

        ArrayList<ProductDTO> productList = new ListView().getProductList();
        while (true){



            System.out.println();
            if (selectList.size() > 0) {
                System.out.println("============선택한 상품 목록입니다============");
                for (int i = 0; i < selectList.size(); i++) {
                    System.out.println((i + 1) + ")" + selectList.get(i).getName() + " | 사이즈: " + selectList.get(i).getSize() + " | 금액: " + selectList.get(i).getPrice() + "원");

                }
            }

            System.out.println("============준비된 상품 목록입니다============");
            for (int i = 0; i < productList.size(); i++) {
                System.out.println((i + 1) + ") " + productList.get(i).getName() + " | 사이즈: " + productList.get(i).getSize() + " | 금액: " + productList.get(i).getPrice() + "원");
            }
            System.out.println("==========================================");

                System.out.print(productList.size()+1+") 선택상품 초기화\n");
                System.out.print(productList.size()+2+") 메인페이지로 돌아가기\n");




            if (selectList.size() > 0) {
                System.out.print(productList.size()+3+") 장바구니가기\n"); // 장바구니호출하기
            }
            System.out.print("선택할 상품을 입력하세요 : ");
            productNumber = sc.nextInt();


            if (productNumber == productList.size()+1) {
                selectList.clear();
            }
            if (productList.size() > productNumber - 1) {
                selectList.add(productList.get(productNumber - 1));
            }

            if (productNumber == productList.size()+2) {
                break;
            }
            if (productNumber == 18){
                CartController ct = new CartController();
                ct.SbList = selectList;
                ct.shopBasket();
            }

        }
    }


    public ArrayList<ProductDTO> getSelectLists(){  // 선택한 상품목록 메소드
        return selectList;
    }





}

