# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import dtk.dtkCore as dtk

import unittest

class BoxTest(unittest.TestCase):

    def test_members(self):
        b2 = dtk.Box2I()
        self.assertEqual(b2.min, dtk.V2I())
        self.assertEqual(b2.max, dtk.V2I())
        b3 = dtk.Box3F()
        self.assertEqual(b3.min, dtk.V3F())
        self.assertEqual(b3.max, dtk.V3F())
        
        min2 = dtk.V2I(1, 2)
        max2 = dtk.V2I(3, 4)
        b2 = dtk.Box2I(min2, max2)
        self.assertEqual(b2.min, min2)
        self.assertEqual(b2.max, max2)
        self.assertEqual(1, b2.x)
        self.assertEqual(2, b2.y)
        self.assertEqual(3, b2.w)
        self.assertEqual(3, b2.h)
        min3 = dtk.V3F(1, 2, 3)
        max3 = dtk.V3F(4, 5, 6)
        b3 = dtk.Box3F(min3, max3)
        self.assertEqual(b3.min, min3)
        self.assertEqual(b3.max, max3)
        self.assertEqual(1, b3.x)
        self.assertEqual(2, b3.y)
        self.assertEqual(3, b3.z)
        self.assertEqual(3, b3.w)
        self.assertEqual(3, b3.h)
        self.assertEqual(3, b3.d)
        
        size2 = dtk.Size2I(3, 2)
        b2 = dtk.Box2I(min2, size2)
        self.assertEqual(min2, b2.min)
        self.assertEqual(dtk.V2I(3, 3), b2.max)
        self.assertEqual(size2, b2.size)
        min2 = dtk.V2F(1, 2)
        size2 = dtk.Size2F(3, 2)
        b2 = dtk.Box2F(min2, size2)
        self.assertEqual(min2, b2.min)
        self.assertEqual(dtk.V2F(4, 4), b2.max)
        self.assertEqual(size2, b2.size)
        size3 = dtk.Size3F(4, 5, 6)
        b3 = dtk.Box3F(min3, size3)
        self.assertEqual(min3, b3.min)
        self.assertEqual(dtk.V3F(5, 7, 9), b3.max)
        self.assertEqual(size3, b3.size)

    def test_functions(self):
        b3 = dtk.Box3F(1, 2, 3, 4, 5, 6)
        c = dtk.center(b3)
        self.assertEqual(dtk.V3F(3, 4.5, 6), c)
        
        b2 = dtk.Box2F(1, 2, 3, 4)
        a = dtk.area(b2)
        self.assertEqual(12, a)
        
        b3 = dtk.Box3F(1, 2, 3, 4, 5, 6)
        v = dtk.volume(b3)
        self.assertEqual(120, v)
        
        b2 = dtk.Box2I(0, 0, 3, 3)
        self.assertTrue(dtk.contains(b2, dtk.Box2I(0, 0, 1, 1)))
        self.assertFalse(dtk.contains(b2, dtk.Box2I(-1, -1, 1, 1)))
        self.assertTrue(dtk.contains(b2, dtk.V2I(1, 1)))
        self.assertFalse(dtk.contains(b2, dtk.V2I(-1, -1)))
        
        b2 = dtk.Box2F(0, 0, 2, 2)
        self.assertTrue(dtk.contains(b2, dtk.Box2F(0, 0, 1, 1)))
        self.assertFalse(dtk.contains(b2, dtk.Box2F(-1, -1, 1, 1)))
        self.assertTrue(dtk.contains(b2, dtk.V2F(1, 1)))
        self.assertFalse(dtk.contains(b2, dtk.V2F(-1, -1)))
        
        b2 = dtk.Box2I(0, 0, 3, 3)
        self.assertTrue(dtk.intersects(b2, dtk.Box2I(-1, -1, 2, 2)))
        self.assertFalse(dtk.intersects(b2, dtk.Box2I(-2, -2, 2, 2)))
        b2a = dtk.intersect(b2, dtk.Box2I(-1, -1, 2, 2))
        self.assertEqual(dtk.Box2I(0, 0, 1, 1), b2a)

        b2 = dtk.Box2F(0, 0, 2, 2)
        self.assertTrue(dtk.intersects(b2, dtk.Box2F(-1, -1, 2, 2)))
        self.assertFalse(dtk.intersects(b2, dtk.Box2F(-2, -2, 1, 1)))
        b2a = dtk.intersect(b2, dtk.Box2F(-1, -1, 2, 2))
        self.assertEqual(dtk.Box2F(0, 0, 1, 1), b2a)
        
        b2 = dtk.Box2I(1, 2, 3, 4)
        b2a = dtk.expand(b2, dtk.Box2I(1, 2, 4, 5))
        b2b = dtk.expand(b2, dtk.V2I(4, 5))
        self.assertEqual(dtk.Box2I(1, 2, 4, 5), b2a)
        self.assertEqual(dtk.Box2I(1, 2, 4, 4), b2b)
        
        b2 = dtk.Box2I(1, 2, 3, 4)
        b2a = dtk.margin(b2, dtk.V2I(1, 2))
        b2b = dtk.margin(b2, 1)
        b2c = dtk.margin(b2, 1, 2, 3, 4)
        self.assertEqual(dtk.Box2I(0, 0, 5, 8), b2a)
        self.assertEqual(dtk.Box2I(0, 1, 5, 6), b2b)
        self.assertEqual(dtk.Box2I(0, 0, 7, 10), b2c)

    def test_operators(self):
        self.assertEqual(dtk.Box2I(1, 2, 3, 4), dtk.Box2I(1, 2, 3, 4))
        self.assertNotEqual(dtk.Box2I(1, 2, 3, 4), dtk.Box2I(4, 3, 2, 1))

if __name__ == '__main__':
    unittest.main()
