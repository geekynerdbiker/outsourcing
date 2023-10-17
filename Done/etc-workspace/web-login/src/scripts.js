/* /////////////// DATA STRUCTURES /////////////// */
let user = {
    firstName: "",
    lastName: "",
    gender: "",
    mail: "",
    password: "_",
};

let login = {
    mail: "",
    password: "",
};

let errorLog = {
    mail: false,
    password: false,
};

let errorSingUp = {
    firstName: false,
    lastName: false,
    gender: false,
    mail: false,
    password: false,
    confPassword: false,
};

$(document).ready(function() {
    $("#singupPage").hide();
    $("#loggedPage").hide();
    $("#signedPage").hide();
    $("#loginBtn").css({ "border-top": "5px solid var(--main)", "color": "black", "background-color": "white" });
    clean();

    function clean() {
        $(".errorBox").hide();
        $(".checkMark").hide();
        $(".inputBox div").css("border", "");
        $("#male").prop('checked', false);
        $("#female").prop('checked', false);
    };

    $("#loginBtn").click(function() {
        $("#loginBtn").css({ "border-top": "5px solid var(--main)", "color": "black", "background-color": "white" });
        $("#singupBtn").css({ "border-top": "", "color": "", "background-color": "" });
        $("#loginPage").show();
        $("#singupPage").hide();
        $("#loggedPage").hide();
        $("#signedPage").hide();
    });

    $("#singupBtn").click(function() {
        $("#singupBtn").css({ "border-top": "5px solid var(--main)", "color": "black", "background-color": "white" });
        $("#loginBtn").css({ "border-top": "", "color": "", "background-color": "" });
        $("#loginPage").hide();
        $("#singupPage").show();
        $("#loggedPage").hide();
        $("#signedPage").hide();
    });

    $("section").click(input => check(input));
    $("section").keyup(input => check(input));

    function check(input) {
        if (input.target.id === "emailLog") checkMailLog();
        else if (input.target.id === "passwordLog") checkPasswordLog();
        else if (input.target.id === "firstName") checkFirstName();
        else if (input.target.id === "lastName") checkLastName();
        else if (input.target.id === "male") checkGender();
        else if (input.target.id === "female") checkGender();
        else if (input.target.id === "emailSingUp") checkMailSingUp();
        else if (input.target.id === "passwordSingUp") checkPasswordSingUp();
        else if (input.target.id === "confPassword") checkConfPassword();
    };

    function checkAll(type) {
        if (type === "logCommit") {
            checkMailLog();
            checkPasswordLog();
        } else if (type === "singUpCommit") {
            checkFirstName();
            checkLastName();
            checkGender();
            checkMailSingUp();
            checkPasswordSingUp();
            checkConfPassword();
        }
    };

    function checkMailLog() {
        let pattern = /^([\w-\.]+@([\w-]+\.)+[\w-]{2,4})?$/;
        let email = $("#emailLog").val();
        if (pattern.test(email) && email !== "") {
            $("#logMailError").hide()
            $("#emailErrorMessageLog").html("");
            $("#c11").show();
            $("#b11").css("border", "");
            errorLog.mail = true;
            login.mail = email;
        } else {
            $("#b11").css("border", "1px solid red");
            $("#c11").hide();
            errorLog.mail = false;
            $("#logMailError").show();
            if (email === "") {
                $("#logMailError").html("Please enter your email!");
            } else {
                $("#logMailError").html("Your email adress is invalid!");
            }
        }
    }

    function checkPasswordLog() {
        let password = $("#passwordLog").val();
        let len = password.length;
        if (/[A-Z]/.test(password) && /[a-z]/.test(password) && /[0-9]/.test(password) &&
            /[@#$%^&+=]/.test(password) && len >= 6) {
            $("#logPasswordError").hide();
            $("#c12").show();
            $("#b12").css("border", "");
            errorLog.password = true;
            login.password = password;
        } else {
            $("#logPasswordError").show();
            $("#b12").css("border", "1px solid red");
            errorLog.password = false;
            if (len === 0) $("#logPasswordError").html("Please enter your password!");
            else if (len < 6) $("#logPasswordError").html("At least 6 characters!");
            else if (/[A-Z]/.test(password) === false) $("#logPasswordError").html("At least one capital letter!");
            else if (/[a-z]/.test(password) === false) $("#logPasswordError").html("At least one lowercase letter!");
            else if (/[0-9]/.test(password) === false) $("#logPasswordError").html("At least one number!");
            else if (/[@#$%^&+=]/.test(password) === false) $("#logPasswordError").html("At least one special character!");
        }
    }

    function checkFirstName() {
        let name = $("#firstName").val();
        let len = name.length;
        if (/[A-Z]/.test(name[0]) && /[A-Z]/.test(name) && /[a-z]/.test(name) && !(/[0-9]/.test(name)) &&
            !(/[@#$%^&+=]/.test(name)) && len > 0) {
            $("#firstNameError").hide();
            $("#c21").show();
            $("#b21").css("border", "");
            user.firstName = name;
            errorSingUp.firstName = true;
        } else {
            $("#firstNameError").show();
            $("#b21").css("border", "1px solid red");
            errorSingUp.firstName = false;
            if (len === 0) $("#firstNameError").html("Please enter your first name!");
            else if (/[A-Z]/.test(name[0]) === false) $("#firstNameError").html("Name should start with a capital letter");
            else if (/[0-9]/.test(password)) $("#firstNameError").html("Name shouldn't include any numbers!");
            else if (/[@#$%^&+=]/.test(password)) $("#firstNameError").html("Name shouldn't include any special characters!");
        }
    };

    function checkLastName() {
        let name = $("#lastName").val();
        let len = name.length;
        if (/[A-Z]/.test(name[0]) && /[A-Z]/.test(name) && /[a-z]/.test(name) && !(/[0-9]/.test(name)) &&
            !(/[@#$%^&+=]/.test(name)) && len > 0) {
            $("#lastNameError").hide();
            $("#c22").show();
            $("#b22").css("border", "");
            user.lastName = name;
            errorSingUp.lastName = true;
        } else {
            $("#lastNameError").show();
            $("#b22").css("border", "1px solid red");
            errorSingUp.lastName = false;
            if (len === 0) $("#lastNameError").html("Please enter your last name!");
            else if (/[A-Z]/.test(name[0]) === false) $("#lastNameError").html("Name should start with a capital letter");
            else if (/[0-9]/.test(password)) $("#lastNameError").html("Name shouldn't include any numbers!");
            else if (/[@#$%^&+=]/.test(password)) $("#lastNameError").html("Name shouldn't include any special characters!");
        }
    };

    function checkGender() {
        let male = $("#male").prop("checked");
        let female = $("#female").prop("checked");

        if (!male && !female) {
            $("#genderError").html("Please enter your gender!");
            $("#genderError").show();
            $("#c23").hide();
            errorSingUp.gender = false;
        } else {
            $("#genderError").hide();
            $("#c23").show();
            user.gender = male ? "male" : "female";
            errorSingUp.gender = true;
        }
    }

    function checkMailSingUp() {
        let pattern = /^([\w-\.]+@([\w-]+\.)+[\w-]{2,4})?$/;
        let email = $("#emailSingUp").val();
        if (pattern.test(email) && email !== "") {
            $("#singUpMailError").hide()
            $("#emailErrorMessageLog").html("");
            $("#c24").show();
            $("#b24").css("border", "");
            user.mail = email;
            errorSingUp.mail = true;
        } else {
            $("#b24").css("border", "1px solid red");
            $("#c24").hide();
            errorSingUp.mail = false;
            $("#singUpMailError").show();
            if (email === "") {
                $("#singUpMailError").html("Please enter your email!");
            } else {
                $("#singUpMailError").html("Your email adress is invalid!");
            }
        }
    };

    function checkPasswordSingUp() {
        let password = $("#passwordSingUp").val();
        let len = password.length;
        if (/[A-Z]/.test(password) && /[a-z]/.test(password) && /[0-9]/.test(password) &&
            /[@#$%^&+=]/.test(password) && len >= 6) {
            $("#singUpPasswordError").hide();
            $("#c25").show();
            $("#b25").css("border", "");
            user.password = password;
            errorSingUp.password = true;
        } else {
            $("#singUpPasswordError").show();
            $("#b25").css("border", "1px solid red");
            errorSingUp.password = false;
            if (len === 0) $("#singUpPasswordError").html("Please enter your password!");
            else if (len < 6) $("#singUpPasswordError").html("At least 6 characters!");
            else if (/[A-Z]/.test(password) === false) $("#singUpPasswordError").html("At least one capital letter!");
            else if (/[a-z]/.test(password) === false) $("#singUpPasswordError").html("At least one lowercase letter!");
            else if (/[0-9]/.test(password) === false) $("#singUpPasswordError").html("At least one number!");
            else if (/[@#$%^&+=]/.test(password) === false) $("#singUpPasswordError").html("At least one special character!");
        }
    }

    function checkConfPassword() {
        let confPassword = $("#confPassword").val();
        let len = confPassword.length;
        if (user.password === confPassword) {
            $("#confPasswordError").hide();
            $("#b26").css("border", "");
            $("#c26").show();
            errorSingUp.confPassword = true;
        } else {
            $("#confPasswordError").show();
            $("#c26").hide();
            $("#b26").css("border", "1px solid red");
            errorSingUp.confPassword = false;
            if (len === 0) $("#confPasswordError").html("Please re-enter your password!");
            else $("#confPasswordError").html("Password doesn't match!");
        }
    };

    $("#singUp").click(function() {
        checkAll("singUpCommit");

        if (Object.values(errorSingUp).every(item => item === true)) {
            $("#singupPage").hide();
            $("#signedPage").show();
            resetAll();
        } else {
            console.log("Not Yet!");
        }
    });

    $("#login").click(function() {
        checkAll("loginCommit");

        if ((Object.values(errorSingUp).every(item => item === true)) &&
            user.mail === login.mail && user.password === user.password) {
            $("#loginPage").hide();
            $("#loggedPage").show();
            resetAll();
        } else {
            console.log("Not Yet!");
            $("#credentials").css("color", "red");
            $("#credentials").html("Credential do not match!");
        }
    });

    function resetAll() {
        clean();
        $("#emailLog").val("");
        $("#passwordLog").val("");

        $("#firstName").val("");
        $("#lastName").val("");
        $("#emailSingUp").val("");
        $("#passwordSingUp").val("");
        $("#confPassword").val("");
    };
});