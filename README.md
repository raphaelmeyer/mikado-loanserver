# Mikado Method Example Code

[![Build Status](https://travis-ci.org/raphaelmeyer/mikado-loanserver.svg?branch=master)](https://travis-ci.org/raphaelmeyer/mikado-loanserver)

A code snippet to exercise [The Mikado Method](https://www.manning.com/books/the-mikado-method).

The Mikado Method is described in the [book](https://www.manning.com/books/the-mikado-method)
with the same title.

The [code](https://github.com/mikadomethod/book-chapter-5-code) is from chapter 5 of the same
book.
The code is translated to C# and C++.


## Web Service API

```
http://localhost:8080/?action=apply&amount=500000&contact=johanna.muster@bbv.ch

  [{ "id" : 1 }]
```

```
http://localhost:8080/?action=fetch&ticketId=1

  [{
    "amount" : 500000, "application_no" : 1,  "approved" : false,
    "contact":"johanna.muster@bbv.ch"
  }]
```

```
http://localhost:8080/?action=approve&ticketId=1

  [{ "id" : 1 }]
```

```
http://localhost:8080/?action=fetch&ticketId=1

  [{
    "amount" : 500000, "application_no" : 1, "approved" : true,
    "contact" : "johanna.muster@bbv.ch"
  }]
```

## Exercises

1. Add some tests for the approval process.
2. Move control over ID generation (getNextID) to LoanRepository.
3. Split the loan server into two separated servers: one to handle loan applications, and the other to handle approvals.
