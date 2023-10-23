package com.teamproject.hamster.controller;

import com.teamproject.hamster.dto.ProductDTO;
import com.teamproject.hamster.view.ListView;

import java.util.ArrayList;
import java.util.Scanner;

public class ProductController {
    // 필드의 변수로 전역으로 선택된 상품을 관리하기위한 ArrayList객체를 생성
    private ArrayList<ProductDTO> selecttList = new ArrayList<>();
    private ProductDTO[] productList2 = new ProductDTO[10];
    private Scanner sc = new Scanner(System.in);

    // 사용자가 선택한 정보를 담기위한 용도의 메소드
    public void selectProduct() {
        // 상품고르는 화면을 그려주기
        System.out.print("신발선택화면");
        System.out.print("신발종류를 선택하세요 : ");
        // 입력된 상품의 객체정보를 담아놓은 객체
        ArrayList<ProductDTO> productList = new ListView().getProductList();

        selecttList.add(productList.get(0));
        selecttList.add(productList.get(4));
        System.out.println(selecttList);
        int no = sc.nextInt();

        // 선택이 다끝나면 출력문으로 장바구니로 이동합니다. 라고 출력
//        ShopBasket shopBasket = new ShopBasket();
//        shopBasket.selectProduct(selecttList); // 장바구니 화면으로 이동하는 소스
    }

    public void paymentMethody(ArrayList<ProductController> payment) {

        ArrayList<ProductDTO> payList = new ArrayList<>();
        payList.add(new ProductDTO("나이키 인피니티 런", 240, 80000));
        payList.add(new ProductDTO("나이키 인피니티 런", 250, 80000));
        payList.add(new ProductDTO("나이키 인피니티 런", 260, 80000));

        System.out.println("결제하실 상품목록은 아래와 같습니다. ");
        for (int i = 0; i < payList.size(); i++) {
            System.out.println(payList.get(i));
        }
    }
}
