var yscreen = window.screen.height;
function show(){
    about.classList.toggle("close_about");
}
function slide(sec){
    var plate = document.querySelectorAll("#plate");
    for (i=0; i<(5); i++){
        if (i!= sec){
            plate[i].style.opacity = "0";
            plate[i].style.transform = "translate(0) rotateY(45deg)";
        }
    }
    plate[sec].style.opacity = "1";
    plate[sec].style.transform = "translate(-50%) rotateY(0deg)";
}
function op_member(){
    member.style.opacity = "100%";
    member.style.zIndex = "1";
    text_code.style.opacity = "0%";
    text_code.style.zIndex = "-1";
}
function op_text(){
    member.style.opacity = "0%";
    member.style.zIndex = "-1";
    text_code.style.opacity = "100%";
    text_code.style.zIndex = "1";
}

