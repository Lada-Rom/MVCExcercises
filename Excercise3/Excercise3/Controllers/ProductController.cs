using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Excercise3.Controllers
{
    public class ProductController : Controller
    {
        //
        // GET: /Product/

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult GenerateCollection()
        {
            List<Models.Product> products = new List<Models.Product>();
            for (int i = 0; i < 10; i++)
            {
                products.Add(new Models.Product()
                {
                    ID = i + 1,
                    Name = "Item Name " + i,
                    Price = (i + 1) * 2,
                    CreatedDate = DateTime.Today
                });
            }
            return View(products);
        }

    }
}
