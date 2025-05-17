
const dbUrl = "https://dht11-fbbb3-default-rtdb.firebaseio.com/DHT11.json";


async function fetchData() {

    try {

        const response = await fetch(dbUrl);

        if (!response.ok) {

            throw new Error(`HTTP error! Status: ${response.status}`);

        }

        const data = await response.json();


        if (data && data.Temperature !== undefined && data.Humidity !== undefined) {

            document.getElementById("temperature").innerText = `Temperature: ${data.Temperature}°C`;

            document.getElementById("humidity").innerText = `Humidity: ${data.Humidity}%`;

        } else {

            console.error("Data format error or missing values.");

        }

    } catch (error) {

        console.error("Error fetching data:", error);

    }

}

    
// Fetch data every 5 seconds

setInterval(fetchData, 3000);

fetchData();