﻿// --------------------------------------------------------------------------------------------------------------------
// <copyright file="ReflectionMathTests.cs" company="PropertyTools">
//   Copyright (c) 2014 PropertyTools contributors
// </copyright>
// --------------------------------------------------------------------------------------------------------------------

namespace PropertyTools.Wpf.Tests
{
    using System;
    using System.Globalization;
    using System.Windows;
    using NUnit.Framework;

    [TestFixture]
    public class ReflectionMathTests
    {
        [Test]
        public void TryAdd_Numbers_ReturnsVector()
        {
            object r;
            Assert.IsTrue(ReflectionMath.TryAdd(1, 1, out r));
            Assert.AreEqual(2, r);
            Assert.IsTrue(ReflectionMath.TryAdd(1d, 1d, out r));
            Assert.AreEqual(2, r);
            Assert.IsTrue(ReflectionMath.TryAdd(1, 1d, out r));
            Assert.AreEqual(2, r);
            Assert.IsTrue(ReflectionMath.TryAdd(1d, 1, out r));
            Assert.AreEqual(2, r);
        }

        [Test]
        public void TryMultiply_Numbers_ReturnsVector()
        {
            object r;
            Assert.IsTrue(ReflectionMath.TryMultiply(2, 1, out r));
            Assert.AreEqual(2, r);
            Assert.IsTrue(ReflectionMath.TryMultiply(2d, 1d, out r));
            Assert.AreEqual(2, r);
            Assert.IsTrue(ReflectionMath.TryMultiply(2, 1d, out r));
            Assert.AreEqual(2, r);
            Assert.IsTrue(ReflectionMath.TryMultiply(2d, 1, out r));
            Assert.AreEqual(2, r);
        }
        [Test]
        public void TryMultiply_Vector_ReturnsVector()
        {
            var v1 = new Vector(10, 10);
            var v2 = v1 * 4;
            object v3;
            Assert.IsTrue(ReflectionMath.TryMultiply(v1, 4.0, out v3));
            Assert.AreEqual(v2, v3);
        }

        [Test]
        public void TrySubtract_DateTime_ReturnsTimeSpan()
        {
            var t1 = DateTime.Now;
            var t2 = t1.AddDays(2);
            object d;
            Assert.IsTrue(ReflectionMath.TrySubtract(t2, t1, out d));
            Assert.IsTrue(d is TimeSpan);
            Assert.AreEqual(2, ((TimeSpan)d).TotalDays);
        }

        [Test]
        public void TrySubtract_Doubles_ReturnsDouble()
        {
            double n1 = 10;
            double n2 = 12;
            object d;
            Assert.IsTrue(ReflectionMath.TrySubtract(n2, n1, out d));
            Assert.IsTrue(d is double);
            Assert.AreEqual(2, (double)d);
        }

        [Test]
        public void TrySubtract_Ints_ReturnsDouble()
        {
            int n1 = 10;
            int n2 = 12;
            object d;
            Assert.IsTrue(ReflectionMath.TrySubtract(n2, n1, out d));
            Assert.IsTrue(d is int);
            Assert.AreEqual(2, (int)d);
        }

        [Test]
        public void TrySubtract_PointFromVector_Fails()
        {
            object r;
            Assert.IsFalse(ReflectionMath.TrySubtract(new Vector(0, 0), new Point(1, 1), out r));
        }

        [Test]
        public void TrySubtract_Points_ReturnsVector()
        {
            var p1 = new Point(10, 10);
            var p2 = new Point(8, 3);
            var d = p2 - p1;

            object o1 = p1;
            object o2 = p2;
            object d2;
            Assert.IsTrue(ReflectionMath.TrySubtract(o2, o1, out d2));
            Assert.AreEqual(d, d2);
        }

        [Test]
        public void TryParse_Double_ReturnsCorrectValue()
        {
            object pi;
            Assert.IsTrue(ReflectionMath.TryParse(typeof(double), "3.14", CultureInfo.InvariantCulture, out pi));
            Assert.AreEqual(3.14, pi);
        }
    }
}