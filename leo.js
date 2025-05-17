const dbUrl = "https://dht11-fbbb3-default-rtdb.firebaseio.com/state.json";

// Function to send state to Firebase
async function sendState(state) {
    try {
        const response = await fetch(dbUrl, {
            method: "PUT", // Use PUT to update the state
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({ state: state })
        });

        if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
        }

        console.log("State updated successfully");
    } catch (error) {
        console.error("Error sending state:", error);
    }
}

// Example usage: Sending "ON" state
document.getElementById("sendOn").addEventListener("click", () => sendState("ON"));
document.getElementById("sendOff").addEventListener("click", () => sendState("OFF"));
