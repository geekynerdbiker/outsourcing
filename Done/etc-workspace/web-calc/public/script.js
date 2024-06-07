let inputString = '0';
let displayValue = '0';
let selection = '';

function keyboard(e) {
  if (e.keyCode === 27) {
    clearDisplay();
  } else if (e.keyCode === 8 || e.keyCode === 46) {
    backspace();
  } else if (e.keyCode === 13 || e.keyCode === 187) {
    calculate();
  } else if (48 <= e.keyCode && e.keyCode <= 57) {
    input(e.key);
  } else if (96 <= e.keyCode && e.keyCode <= 105) {
    input(e.key);
  }
}

function input(value) {
  if (inputString.length >= 3)
    return;
  if (value == '0' || value == '00') {
    if (inputString == '0')
      return;
  }
  if (inputString == '0') {
    inputString = value;
    displayValue = value;
    document.querySelector('.display').value = displayValue;  
    return;
  }
  inputString += value;
  displayValue += value;
  document.querySelector('.display').value = displayValue;
  }

function calculate() {
    const text = document.querySelector("select[class=selection] option:checked").text;

    document.getElementsByClassName("box1")[0].style.display = "none";
    document.getElementsByClassName("box2")[0].style.display = "block";
    
    var n = parseInt(inputString);

    if (n >= 64 && n < 71) {
      document.querySelector(".display2").value = "안전문 본품";
      document.querySelector('.result').value = '소형';
      add('small', false);
    } else if (n >= 71 && n < 77) {
      document.querySelector('.result').value = '설치 불가';
    } else if (n >= 77 && n < 84) {
      document.querySelector('.result').value = '총 0 개';
    } else if (n >= 84 && n < 90) {
      document.querySelector('.result').value = '총 1 개';
      add('6CM', false);
    } else if (n >= 90 && n < 96) {
      document.querySelector('.result').value = '총 1 개';
      add('12CM', false);
    } else if (n >= 96 && n < 102) {
      document.querySelector('.result').value = '총 1 개';
      add('18CM', false);
    } else if (n >= 102 && n < 108) {
      document.querySelector('.result').value = '총 1 개';
      add('24CM', false);
    } else if (n >= 108 && n < 114) {
      document.querySelector('.result').value = '총 1 개';
      add('30CM', false);
    } else if (n >= 114 && n < 120) {
      document.querySelector('.result').value = '총 1 개';
      add('36CM', false);
    } else if (n >= 120 && n < 126) {
      document.querySelector('.result').value = '총 1 개';
      add('42CM', false);
    } else if (n >= 126 && n < 132) {
      document.querySelector('.result').value = '총 1 개';
      add('48CM', false);
    } else if (n >= 132 && n < 138) {
      document.querySelector('.result').value = '총 1 개';
      add('54CM', false);
    } else if (n >= 138 && n < 144) {
      document.querySelector('.result').value = '총 1 개';
      add('60CM', false);
    } else if (n >= 144 && n < 150) {
      document.querySelector('.result').value = '총 2 개';
      add('6CM');add('60CM');
    } else if (n >= 150 && n < 156) {
      document.querySelector('.result').value = '총 1 개';
      add('72CM', false);
    } else if (n >= 156 && n < 162) {
      document.querySelector('.result').value = '총 2 개';
      add('36CM');add('42CM');
    } else if (n >= 162 && n < 168) {
      document.querySelector('.result').value = '총 1 개';
      add('84CM', false);
    } else if (n >= 168 && n < 174) {
      document.querySelector('.result').value = '총 2 개';
      add('6CM');add('84CM');
    } else if (n >= 174 && n < 180) {
      document.querySelector('.result').value = '총 2 개';
      add('12CM');add('84CM');
    } else if (n >= 180 && n < 186) {
      document.querySelector('.result').value = '총 2 개';
      add('18CM');add('84CM');
    } else if (n >= 186 && n < 192) {
      document.querySelector('.result').value = '총 2 개';
      add('24CM');add('84CM');
    } else if (n >= 192 && n < 198) {
      document.querySelector('.result').value = '총 2 개';
      add('30CM');add('84CM');
    } else if (n >= 198 && n < 204) {
      document.querySelector('.result').value = '총 2 개';
      add('36CM');add('84CM');
    } else if (n >= 204 && n < 210) {
      document.querySelector('.result').value = '총 2 개';
      add('42CM');add('84CM');
    } else if (n >= 210 && n < 216) {
      document.querySelector('.result').value = '총 2 개';
      add('48CM');add('84CM');
    } else if (n >= 216 && n < 222) {
      document.querySelector('.result').value = '총 2 개';
      add('54CM');add('84CM');
    } else if (n >= 222 && n < 228) {
      document.querySelector('.result').value = '총 2 개';
      add('60CM');add('84CM');
    } else if (n >= 228 && n < 234) {
      document.querySelector('.result').value = '총 3 개';
      add('6CM');add('60CM');add('84CM');
    } else if (n >= 234 && n < 240) {
      document.querySelector('.result').value = '총 2 개';
      add('72CM');add('84CM');
    } else if (n >= 240 && n < 246) {
      document.querySelector('.result').value = '총 3 개';
      add('36CM');add('42CM');add('84CM');
    } else if (n >= 246 && n < 252) {
      document.querySelector('.result').value = '총 2 개';
      add('84CM');add('84CM');
    } else if (n >= 252 && n < 258) {
      document.querySelector('.result').value = '총 3 개';
      add('6CM');add('84CM');add('84CM');
    } else if (n >= 258 && n < 264) {
      document.querySelector('.result').value = '총 3 개';
      add('12CM');add('84CM');add('84CM');
    } else if (n >= 264 && n < 270) {
      document.querySelector('.result').value = '총 3 개';
      add('18CM');add('84CM');add('84CM');
    } else if (n >= 270 && n < 276) {
      document.querySelector('.result').value = '총 3 개';
      add('24CM');add('84CM');add('84CM');
    } else if (n >= 276 && n < 282) {
      document.querySelector('.result').value = '총 3 개';
      add('30CM');add('84CM');add('84CM');
    } else if (n >= 282 && n < 288) {
      document.querySelector('.result').value = '총 3 개';
      add('36CM');add('84CM');add('84CM');
    } else if (n >= 288 && n < 294) {
      document.querySelector('.result').value = '총 3 개';
      add('42CM');add('84CM');add('84CM');
    } else if (n >= 294 && n < 300) {
      document.querySelector('.result').value = '총 3 개';
      add('48CM');add('84CM');add('84CM');
    } else {
      document.querySelector('.result').value = '설치 불가';
    }

    if (document.querySelector('.result').value == '설치 불가') {
      add2('이 길이는 설치할 수 없습니다.');
      document.querySelector('.result').value = '총 0 개';
    } else if (document.querySelector('.result').value == '총 0 개') {
      add2('확장 패널이 필요하지 않습니다.');
      document.querySelector('.result').value = '총 0 개';
    } else if (document.querySelector('.result').value == '소형') {
      document.querySelector('.result').value = '총 0 개';
    }

    if (n > 70) {
      document.querySelector(".display2").value = "안전문 표준형 본품";
    }
    
}

  function clearDisplay() {
    inputString = '0';
    displayValue = '0';
    document.querySelector('.display').value = '0';
  }
  
  function backspace() {
    inputString = inputString.slice(0, -1);
    displayValue = displayValue.slice(0, -1);
    
    if (inputString == '')
      inputString = '0';
    if (displayValue == '')
      displayValue = '0';
    document.querySelector('.display').value = displayValue;
  }

  function goback() {
    var con = document.querySelector(".rst_container");

    while (con.firstChild)
      con.removeChild(con.firstChild);

    document.getElementsByClassName("box2")[0].style.display = "none";
    document.getElementsByClassName("box1")[0].style.display = "block";
    document.querySelector("select").value = 'default';
    clearDisplay();
  }

  function add(src, border=true) {
    var con = document.querySelector(".rst_container");

    var box = document.createElement('div');
    if (border)
      box.className = 'rst_box';
    else 
    box.className = 'rst_box_without_border';

    var img = document.createElement('div');
    img.className = 'rst_img';
    img.style.backgroundImage = "url(img/p" + src + ".png)"
    
    var size = document.createElement('div');
    size.className = 'rst_size';
    if (src == 'small')
      size.innerText = '소형';
    else
      size.innerText = src;

    img.appendChild(size);
    box.appendChild(img);
    con.appendChild(box);
  }

  function add2(text) {
    var con = document.querySelector(".rst_container");

    var box = document.createElement('div');
    box.className = 'noneed';
    box.innerText = text;

    con.appendChild(box);
  }