using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Excercise4.Models
{
    public class Registration
    {
        public string Login { get; set; }
        public string Password1 { get; set; }
        public string Password2 { get; set; }
        public string Email { get; set; }

        public Registration(string login, string pass1, string pass2, string email)
        { 
            Login = login;
            Password1 = pass1;
            Password2 = pass2;
            Email = email;
        }
    }
}