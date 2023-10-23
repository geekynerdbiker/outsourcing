package com.teamproject.hamster.view;

import com.teamproject.hamster.dto.ProductDTO;

import java.util.ArrayList;
import java.util.Scanner;

public class ListView {
    ProductDTO pd = new ProductDTO();
    private ArrayList<ProductDTO> productList = null;



    public ListView() {
        productList = new ArrayList<>();
        productList.add(new ProductDTO("나이키 인피니티 런", 240, 80000));
        productList.add(new ProductDTO("나이키 인피니티 런", 250, 80000));
        productList.add(new ProductDTO("나이키 인피니티 런", 260, 80000));
        productList.add(new ProductDTO("캔버스 척테일러", 230, 90000));
        productList.add(new ProductDTO("캔버스 척테일러", 240, 90000));
        productList.add(new ProductDTO("캔버스 척테일러", 250, 90000));
        productList.add(new ProductDTO("스테파노로시 버스", 260, 100000));
        productList.add(new ProductDTO("스테파노로시 버스", 270, 100000));
        productList.add(new ProductDTO("스테파노로시 버스", 280, 100000));
        productList.add(new ProductDTO("아디다스 퍼피랫", 220, 110000));
        productList.add(new ProductDTO("아디다스 퍼피랫", 230, 110000));
        productList.add(new ProductDTO("아디다스 퍼피랫", 240, 110000));
        productList.add(new ProductDTO("퓨마 바리 뮬", 230, 120000));
        productList.add(new ProductDTO("퓨마 바리 뮬", 240, 120000));
        productList.add(new ProductDTO("퓨마 바리 뮬", 260, 120000));


    }


    public ArrayList<ProductDTO> getProductList() {
        return productList;
    }

    public void selectList(){
        Scanner sc = new Scanner(System.in);
        while(true){

            System.out.println("========== 상품 목록 ==========");
            System.out.println("1. 상품 전체 보기");
            System.out.println("2. 상품 사이즈 보기");
            System.out.println("0. 메인페이지로 돌아가기 ");
            System.out.println("원하는 메뉴를 선택해주세요.");
            int select = sc.nextInt();
            if (select == 1 ){
                kindOfShoes();
            } else if (select == 2) {
                System.out.println("1. 나이키 인피니티 런");
                System.out.println("2. 캔버스 척테일러");
                System.out.println("3. 스테파노로시 버스");
                System.out.println("4. 아디다스 퍼피랫");
                System.out.println("5. 퓨마 바리 뮬");
                System.out.print("사이즈를 보고싶은 제품을 선택해주세요 : ");
                int select2 = sc.nextInt();
                sc.nextLine();
                ShoesSize(select2);
            } else if (select == 0) {
                System.out.println("메인페이지로 돌아갑니다.");
                break;
            }
        }
    }

    public void kindOfShoes() {
        ListView mv = new ListView();
        ArrayList<ProductDTO> productList = mv.getProductList();
        for (int i = 0; i < productList.size(); i++) {
            System.out.println("제품 이름 : " + productList.get(i).getName());
            System.out.println("제품 가격 : " + productList.get(i).getPrice());
            i += 2;
        }

    }

    public void ShoesSize(int key) {
        if (key == 1) {
            System.out.print(productList.get(0).getName() + "의 사이즈는 ");
            for (int i = 0; i < 3; i++) {
                if (i < 2) {
                    System.out.print(productList.get(i).getSize() + " ");
                } else {
                    System.out.print(productList.get(i).getSize());
                }
            }
            System.out.println("가 있습니다.");
        } else if (key == 2) {
            System.out.print(productList.get(3).getName() + "의 사이즈는 ");
            for (int i = 3; i < 6; i++) {
                if (i < 5) {
                    System.out.print(productList.get(i).getSize() + " ");
                } else {
                    System.out.print(productList.get(i).getSize());
                }
            }
            System.out.println("가 있습니다.");
        } else if (key == 3) {
            System.out.print(productList.get(6).getName() + "의 사이즈는 ");
            for (int i = 6; i < 9; i++) {
                if (i < 8) {
                    System.out.print(productList.get(i).getSize() + " ");
                } else {
                    System.out.print(productList.get(i).getSize());
                }
            }
            System.out.println("가 있습니다.");
        } else if (key == 4) {
            System.out.print(productList.get(9).getName() + "의 사이즈는 ");
            for (int i = 9; i < 12; i++) {
                if (i < 11) {
                    System.out.print(productList.get(i).getSize() + " ");
                } else {
                    System.out.print(productList.get(i).getSize());
                }
            }
            System.out.println("가 있습니다.");
        } else if (key == 5) {
            System.out.print(productList.get(12).getName() + "의 사이즈는 ");
            for (int i = 12; i < 15; i++) {
                if (i < 14) {
                    System.out.print(productList.get(i).getSize() + " ");
                } else {
                    System.out.print(productList.get(i).getSize());
                }
            }
            System.out.println("가 있습니다.");
        }
    }
}