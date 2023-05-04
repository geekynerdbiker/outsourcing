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
            html2 += `</select><br><button onclick="fn3()" id="submit">Submit</button>`
            const holidaydiv = document.querySelector(".holiday")
            holidaydiv.innerHTML = html2
        }
    }

}

function fn2() {
    var date = document.getElementById("holiday").value;
    var area = document.getElementById("Area").value;
    fetch(`https://hotels4.p.rapidapi.com/locations/search?query=${area}&locale=en_US`, {
            "method": "GET",
            "headers": {
                "x-rapidapi-key": "e873399808msh82ec7a7a80aaac6p127486jsn873a8f6dcb79",
                "x-rapidapi-host": "hotels4.p.rapidapi.com"
            }
        })
        .then((data3) => data3.json())
        .then((id) => getid(id))

    const getid = (data3) => {
        var id = data3.suggestions[0].entities[0].destinationId;
        var parts = date.split('-');
        var mydate = new Date(parts[0], parts[1] - 1, parts[2]);
        var mydate2 = new Date(parts[0], parts[1] - 1, parts[2]);
        mydate.setDate(mydate.getDate() + 2);
        var temp = mydate.toISOString().split("T", 1);
        var date2 = temp[0];
        fetch(`https://hotels4.p.rapidapi.com/properties/list?adults1=1&pageNumber=1&destinationId=${id}&pageSize=25&checkOut=${date2}&checkIn=${date}&sortOrder=PRICE&locale=en_US&currency=USD`, {
                "method": "GET",
                "headers": {
                    "x-rapidapi-key": "e873399808msh82ec7a7a80aaac6p127486jsn873a8f6dcb79",
                    "x-rapidapi-host": "hotels4.p.rapidapi.com"
                }
            })
            .then((data4) => data4.json())
            .then((id) => generateHTML3(id))

        const generateHTML3 = (data4) => {
            var today = new Date();
            var html3 = `<div>Your choosen holiday is on ${date}</div><br>`;
            if (today > mydate2) {
                html3 += `<div>Cannot find hotel for holiday that have already passed</div>`
            } else {
                html3 += `<div>List of Hotels:</div>`
                var i = 0;
                for (i = 0; i < data4.data.body.searchResults.results.length; i++) {
                    html3 += `<li>${data4.data.body.searchResults.results[i].name}</li>`;
                }
            }
            const hotelsdiv = document.querySelector(".hotels")
            hotelsdiv.innerHTML = html3
        }
    }
}

async function fn3() {
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

    try {
        const response = await fetch(url + area + url2, options);
        const result = await response.text();
        console.log(result);
    } catch (error) {
        console.error(error);
    }

    // const url = 'https://hotels4.p.rapidapi.com/properties/v2/list';
    // const options = {
    //     method: 'POST',
    //     headers: {
    //         'content-type': 'application/json',
    //         'X-RapidAPI-Key': 'e873399808msh82ec7a7a80aaac6p127486jsn873a8f6dcb79',
    //         'X-RapidAPI-Host': 'hotels4.p.rapidapi.com'
    //     },
    //     body: {
    //         currency: 'USD',
    //         eapid: 1,
    //         locale: 'en_US',
    //         siteId: 300000001,
    //         destination: {
    //             regionId: '6054439'
    //         },
    //         checkInDate: {
    //             day: 10,
    //             month: 10,
    //             year: 2022
    //         },
    //         checkOutDate: {
    //             day: 15,
    //             month: 10,
    //             year: 2022
    //         },
    //         rooms: [{
    //             adults: 2,
    //             children: [{ age: 5 }, { age: 7 }]
    //         }],
    //         resultsStartingIndex: 0,
    //         resultsSize: 200,
    //         sort: 'PRICE_LOW_TO_HIGH',
    //         filters: {
    //             price: { max: 150, min: 100 }
    //         }
    //     }
    // };

    // try {
    //     const response = await fetch(url, options);
    //     const result = await response.text();
    //     console.log(result);
    // } catch (error) {
    //     console.error(error);
    // }
}

{ "q": "busan", "rid": "7d7c6233d75349a48cd9abb14af76edf", "rc": "OK", "sr": [{ "@type": "gaiaRegionResult", "index": "0", "gaiaId": "602043", "type": "CITY", "regionNames": { "fullName": "Busan, South Korea", "shortName": "Busan", "displayName": "Busan, South Korea", "primaryDisplayName": "Busan", "secondaryDisplayName": "South Korea", "lastSearchName": "Busan" }, "essId": { "sourceName": "GAI", "sourceId": "602043" }, "coordinates": { "lat": "35.179548", "long": "129.075651" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaRegionResult", "index": "1", "gaiaId": "6122748", "type": "POI", "regionNames": { "fullName": "Haeundae Beach, Busan, South Korea", "shortName": "Haeundae Beach", "displayName": "Haeundae Beach, Busan, South Korea", "primaryDisplayName": "Haeundae Beach", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Haeundae Beach" }, "essId": { "sourceName": "GAI", "sourceId": "6122748" }, "coordinates": { "lat": "35.158042", "long": "129.158127" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaRegionResult", "index": "2", "gaiaId": "6052866", "type": "NEIGHBORHOOD", "regionNames": { "fullName": "Haeundae, Busan, South Korea", "shortName": "Haeundae", "displayName": "Haeundae, Busan, South Korea", "primaryDisplayName": "Haeundae", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Haeundae" }, "essId": { "sourceName": "GAI", "sourceId": "6052866" }, "coordinates": { "lat": "35.163113", "long": "129.163544" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaRegionResult", "index": "3", "gaiaId": "6288096", "type": "NEIGHBORHOOD", "regionNames": { "fullName": "Jung-gu, Busan, South Korea", "shortName": "Jung-gu", "displayName": "Jung-gu, Busan, South Korea", "primaryDisplayName": "Jung-gu", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Jung-gu" }, "essId": { "sourceName": "GAI", "sourceId": "6288096" }, "coordinates": { "lat": "35.106501", "long": "129.032581" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaHotelResult", "index": "4", "hotelId": "34488577", "type": "HOTEL", "regionNames": { "fullName": "Lavalse Hotel, Busan, South Korea", "shortName": "Lavalse Hotel", "displayName": "Lavalse Hotel, Busan, South Korea", "primaryDisplayName": "Lavalse Hotel", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Lavalse Hotel" }, "essId": { "sourceName": "LCM", "sourceId": "34488577" }, "coordinates": { "lat": "35.094753", "long": "129.039202" }, "hierarchyInfo": { "country": { "isoCode3": "KOR" } }, "cityId": "602043", "hotelAddress": { "street": "82, Bongnaenaru-ro", "city": "Busan", "province": "" } }, { "@type": "gaiaRegionResult", "index": "5", "gaiaId": "553248621555815217", "type": "POI", "regionNames": { "fullName": "Busan Cultural Center, Busan, South Korea", "shortName": "Busan Cultural Center", "displayName": "Busan Cultural Center, Busan, South Korea", "primaryDisplayName": "Busan Cultural Center", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Busan Cultural Center" }, "essId": { "sourceName": "GAI", "sourceId": "553248621555815217" }, "coordinates": { "lat": "35.12684", "long": "129.09544" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaRegionResult", "index": "6", "gaiaId": "6285562", "type": "POI", "regionNames": { "fullName": "Busan Yachting Center, Busan, South Korea", "shortName": "Busan Yachting Center", "displayName": "Busan Yachting Center, Busan, South Korea", "primaryDisplayName": "Busan Yachting Center", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Busan Yachting Center" }, "essId": { "sourceName": "GAI", "sourceId": "6285562" }, "coordinates": { "lat": "35.160657", "long": "129.141384" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaRegionResult", "index": "7", "gaiaId": "5461328", "type": "AIRPORT", "regionNames": { "fullName": "Busan, South Korea (PUS-Gimhae)", "shortName": "Busan (PUS-Gimhae)", "displayName": "Busan (PUS - Gimhae), South Korea", "primaryDisplayName": "Busan (PUS - Gimhae)", "secondaryDisplayName": "South Korea", "lastSearchName": "Busan (PUS - Gimhae)" }, "essId": { "sourceName": "GAI", "sourceId": "5461328" }, "coordinates": { "lat": "35.169351", "long": "128.949792" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } }, "isMinorAirport": "false" }, { "@type": "gaiaRegionResult", "index": "8", "gaiaId": "553248621564994030", "type": "POI", "regionNames": { "fullName": "Busan Cinema Center, Busan, South Korea", "shortName": "Busan Cinema Center", "displayName": "Busan Cinema Center, Busan, South Korea", "primaryDisplayName": "Busan Cinema Center", "secondaryDisplayName": "Busan, South Korea", "lastSearchName": "Busan Cinema Center" }, "essId": { "sourceName": "GAI", "sourceId": "553248621564994030" }, "coordinates": { "lat": "35.171672", "long": "129.127963" }, "hierarchyInfo": { "country": { "name": "South Korea", "isoCode2": "KR", "isoCode3": "KOR" } } }, { "@type": "gaiaRegionResult", "index": "9", "gaiaId": "6123703", "type": "CITY", "regionNames": { "fullName": "Busana, Ventasso, Emilia-Romagna, Italy", "shortName": "Busana", "displayName": "Busana, Ventasso, Emilia-Romagna, Italy", "primaryDisplayName": "Busana", "secondaryDisplayName": "Ventasso, Emilia-Romagna, Italy", "lastSearchName": "Busana" }, "essId": { "sourceName": "GAI", "sourceId": "6123703" }, "coordinates": { "lat": "44.38011010281339", "long": "10.3263010210896" }, "hierarchyInfo": { "country": { "name": "Italy", "isoCode2": "IT", "isoCode3": "ITA" } } }] }