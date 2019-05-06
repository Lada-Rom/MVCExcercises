using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Excercise4.Controllers
{
    public class HomeController : Controller
    {
        //
        // GET: /Home/
        public List<Models.Logining> listlog = new List<Models.Logining>();
        public List<Models.Registration> listreg = new List<Models.Registration>();

        public ActionResult Index()
        {
            return View();
        }

        [HttpGet]
        public ActionResult LogIn()
        {
            return View();
        }

        [HttpPost]
        public ActionResult LogInPost()
        {
            listlog.Add(new Models.Logining(ViewBag.Login, ViewBag.Password));
            return View();
        }

        [HttpGet]
        public ActionResult Register()
        {
            return View();
        }

        [HttpPost]
        public ActionResult RegisterPost()
        {
            listreg.Add(new Models.Registration(ViewBag.Login, ViewBag.Password1, ViewBag.Password2, ViewBag.Email));
            return View();
        }

    }
}
