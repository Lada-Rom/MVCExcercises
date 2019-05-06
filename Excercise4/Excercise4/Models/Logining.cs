using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Excercise4.Models
{
    public class Logining
    {
        public string Login { get; set; }
        public string Password { get; set; }

        public Logining(string login, string pass)
        { 
            Login = login;
            Password = pass;
        }
    }
}