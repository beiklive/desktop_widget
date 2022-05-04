$(function () {
    HTMLCanvasElement.prototype.draw = function (alpha, radius, line, width, sec, direction) {
        var context = this.getContext("2d"),
            start = 0;
        for (var i = 0; i < line.length; i++) {
            line[i] = line[i] * radius / 2 * Math.PI / 180;
        }
        context.beginPath();
        context.strokeStyle = "#3498db";
        context.globalAlpha = alpha;
        context.lineWidth = width;
        context.setLineDash(line);
        context.arc(125, 125, radius / 2, start - Math.PI * 0.5, start + Math.PI * 1.5, false);
        context.stroke();
        if (sec == 0)return;
        setInterval(function draw() {
            context.clearRect(0, 0, 250, 250);
            if (direction)
                start += Math.PI * 2 / sec / 1000 * (1000 / 60);
            else
                start -= Math.PI * 2 / sec / 1000 * (1000 / 60);

            if (start >= Math.PI * 2) {
                start -= Math.PI * 2
            }
            if (start <= -Math.PI * 2) {
                start += Math.PI * 2
            }
            context.beginPath();
            context.strokeStyle = "#3498db";
            context.globalAlpha = alpha;
            context.lineWidth = width;
            context.setLineDash(line);
            context.arc(125, 125, radius / 2, start - Math.PI * 0.5, start + Math.PI * 1.5, false);
            context.stroke();
        }, 1000 / 60);
    }

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.6, 230, [0, 110, 45, 110, 10, 5, 70, 0, 10], 5, 25, true);

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.4, 210, [0, 90, 100, 110, 50], 3, 16, false);

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.3, 190, [0, 30, 5, 3, 60, 130, 5, 3, 90, 34], 5, 20, true);

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.5, 180, [30, 80, 110, 80, 40, 20], 3, 18, false);

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.7, 130, [0, 60, 30, 130, 45, 95], 10, 15, true);

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.5, 110, [0, 30, 230, 100], 3, 6, false);

    var canvas = document.createElement("canvas");
    document.getElementsByClassName("box")[0].appendChild(canvas);
    canvas.setAttribute("class", "img mid");
    canvas.setAttribute("width", "250px");
    canvas.setAttribute("height", "250px");
    canvas.draw(0.6, 100, [130, 120, 110], 3, 4, true);

    Date.prototype.format = function (format) {
        var o = {
            "M+": this.getMonth() + 1, //month
            "d+": this.getDate(), //day
            "h+": this.getHours(), //hour
            "m+": this.getMinutes(), //minute
            "s+": this.getSeconds(), //second
            "q+": Math.floor((this.getMonth() + 3) / 3), //quarter
            "S": this.getMilliseconds() //millisecond
        }
        if (/(y+)/.test(format)) format = format.replace(RegExp.$1,
            (this.getFullYear() + "").substr(4 - RegExp.$1.length));
        for (var k in o)if (new RegExp("(" + k + ")").test(format))
            format = format.replace(RegExp.$1,
                RegExp.$1.length == 1 ? o[k] :
                    ("00" + o[k]).substr(("" + o[k]).length));
        return format;
    }

    function date() {
        var date = new Date();
        $('.time').text(date.format("hh:mm"));

        $('.rotate').remove();
        var angel = 360 * new Date().getSeconds() / 60;
        canvas = document.createElement("canvas");
        document.getElementsByClassName("box")[0].appendChild(canvas);
        canvas.setAttribute("class", "img mid rotate");
        canvas.setAttribute("width", "250px");
        canvas.setAttribute("height", "250px");
        canvas.draw(1, 60, [0, angel, 6, 354 - angel], 3, 0, true);

    }

    date();
    setInterval(date, 1000);
})