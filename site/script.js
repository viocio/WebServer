document.addEventListener("DOMContentLoaded", () => {
  const btn = document.getElementById("btn");
  const msg = document.getElementById("message");

  btn.addEventListener("click", () => {
    msg.textContent = "JavaScript loaded and executed!";
  });
});
