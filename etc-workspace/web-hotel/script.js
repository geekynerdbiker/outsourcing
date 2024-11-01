function fn1() {
    var area = document.getElementById("Area").value;

    const weatherapiurl = `https://api.openweathermap.org/data/2.5/weather?q=${area}&appid=e5eb20914f993f76ee41d0eabe52ab75`;
    fetch(weatherapiurl)
        .then((data) => data.json())
        .then((weather) => generateHTML(weather))

    const generateHTML = (data) => {
        const html = `
            <div class="weather">Current Weather: ${data.weather[0].description}</div>
            <div class="temperature">Current Temperature ${Math.round((data.main.temp-273.15)*100)/100}</div><br>
        `
        const weatherdiv = document.querySelector(".weather")
        weatherdiv.innerHTML = html

        const holidayapiurl = `https://calendarific.com/api/v2/holidays?&api_key=64931719ef8200ea2c7013311cbf0a7717f422ab&country=${data.sys.country}&year=2021`;
        fetch(holidayapiurl)
            .then((data2) => data2.json())
            .then((holiday) => generateHTML2(holiday))

        const generateHTML2 = (data2) => {
            var html2 = `<div>Choose a Holiday</div><select name="holiday" id="holiday">`
            var i = 0;
            for (i = 0; i < data2.response.holidays.length; i++) {
                html2 += `<option value=${data2.response.holidays[i].date.iso}>${data2.response.holidays[i].name}</option>`;
            }
            html2 += `</select><br><button onclick="fn2()" id="submit">Submit</button>`
            const holidaydiv = document.querySelector(".holiday")
            holidaydiv.innerHTML = html2
        }
    }

}

function fn2() {
    var date = document.getElementById("holiday").value;
    var area = document.getElementById("Area").value;

    var url = 'https://hotels4.p.rapidapi.com/locations/v3/search?q=';
    var url2 = '&locale=en_US&langid=1033&siteid=300000001';
    const options = {
        method: 'GET',
        headers: {
            'X-RapidAPI-Key': 'e873399808msh82ec7a7a80aaac6p127486jsn873a8f6dcb79',
            'X-RapidAPI-Host': 'hotels4.p.rapidapi.com'
        }
    };

    fetch(url + area + url2, options)
        .then((data3) => data3.json())
        .then((res) => generateHTML3(res));

    const generateHTML3 = (data3) => {
        var html3 = `<br><div>List of Hotels Available:</div>`
        var i = 0;
        for (i = 0; i < data3.sr.length; i++) {
            if (data3.sr[i].type == "HOTEL")
                html3 += `<li>${data3.sr[i].regionNames.fullName}</br></li>`;
        }
        const hotelsdiv = document.querySelector(".hotels")
        hotelsdiv.innerHTML = html3
    }
}