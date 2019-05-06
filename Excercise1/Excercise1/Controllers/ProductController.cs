using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Excercise1.Controllers
{
    public class ProductController : Controller
    {
        //
        // GET: /Product/

        public ActionResult Index()
        {
            List<Models.Product> products = new List<Models.Product>();

            products.Add(new Models.Product(1, "Pen", 10, "Pen"));
            products.Add(new Models.Product(2, "Eraser", 20, "Eraser"));
            products.Add(new Models.Product(3, "Pencil", 30, "Pencil"));

            return View(products);
        }

    }
}
