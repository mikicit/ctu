// alert('test');

// if (confirm('hi') === true) {
//     alert('Super')
// }

// function showDiolog(text) {
//     const a = 10;
//     alert(text);
// }

// showDiolog('test');

function validate(e) {
    e.preventDefault();
    const errorsBlock = document.querySelector("#errors");
    const nameInput = document.querySelector('#name');
    const emailInput = document.querySelector('#email');

    let errors = [];

    if (nameInput.value.length < 6) {
        errors.push('Length Error');
    }

    if (emailInput.value.length < 2) {
        errors.push('Email Error');
    }

    if (errors.length > 0) {
        errors.forEach((item) => {
            errorsBlock.innerHTML = '<p>' + item + '</p>';
        });

        return;
    }

    console.log(e);
}

function init() {
    const form = document.querySelector('#login-form');
    form.addEventListener('submit', validate);
}

window.onload = init;