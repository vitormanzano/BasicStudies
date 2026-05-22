// Toca o tema de Invencível ao clicar na palavra "invincible" do rodapé.
// Como o rodapé aparece em todas as páginas, este mesmo script serve para todas.

const trigger = document.getElementById("play-invincible");

if (trigger) {
    const audio = new Audio("./src/invincible-title-car-sound.mp3");

    trigger.addEventListener("click", () => {
        if (audio.paused) {
            audio.play();           
        } else {
            audio.pause();     
            audio.currentTime = 0;
        }
    });
}
