# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import tinygfx.tgCore as tg

import unittest

class BoxTest(unittest.TestCase):

    def test_members(self):
        b2 = tg.Box2I()
        self.assertEqual(b2.min, tg.V2I())
        self.assertEqual(b2.max, tg.V2I())
        b3 = tg.Box3F()
        self.assertEqual(b3.min, tg.V3F())
        self.assertEqual(b3.max, tg.V3F())
        
        min2 = tg.V2I(1, 2)
        max2 = tg.V2I(3, 4)
        b2 = tg.Box2I(min2, max2)
        self.assertEqual(b2.min, min2)
        self.assertEqual(b2.max, max2)
        self.assertEqual(1, b2.x)
        self.assertEqual(2, b2.y)
        self.assertEqual(3, b2.w)
        self.assertEqual(3, b2.h)
        min3 = tg.V3F(1, 2, 3)
        max3 = tg.V3F(4, 5, 6)
        b3 = tg.Box3F(min3, max3)
        self.assertEqual(b3.min, min3)
        self.assertEqual(b3.max, max3)
        self.assertEqual(1, b3.x)
        self.assertEqual(2, b3.y)
        self.assertEqual(3, b3.z)
        self.assertEqual(3, b3.w)
        self.assertEqual(3, b3.h)
        self.assertEqual(3, b3.d)
        
        size2 = tg.Size2I(3, 2)
        b2 = tg.Box2I(min2, size2)
        self.assertEqual(min2, b2.min)
        self.assertEqual(tg.V2I(3, 3), b2.max)
        self.assertEqual(size2, b2.size)
        min2 = tg.V2F(1, 2)
        size2 = tg.Size2F(3, 2)
        b2 = tg.Box2F(min2, size2)
        self.assertEqual(min2, b2.min)
        self.assertEqual(tg.V2F(4, 4), b2.max)
        self.assertEqual(size2, b2.size)
        size3 = tg.Size3F(4, 5, 6)
        b3 = tg.Box3F(min3, size3)
        self.assertEqual(min3, b3.min)
        self.assertEqual(tg.V3F(5, 7, 9), b3.max)
        self.assertEqual(size3, b3.size)

    def test_functions(self):
        b3 = tg.Box3F(1, 2, 3, 4, 5, 6)
        c = tg.center(b3)
        self.assertEqual(tg.V3F(3, 4.5, 6), c)
        
        b2 = tg.Box2F(1, 2, 3, 4)
        a = tg.area(b2)
        self.assertEqual(12, a)
        
        b3 = tg.Box3F(1, 2, 3, 4, 5, 6)
        v = tg.volume(b3)
        self.assertEqual(120, v)
        
        b2 = tg.Box2I(0, 0, 3, 3)
        self.assertTrue(tg.contains(b2, tg.Box2I(0, 0, 1, 1)))
        self.assertFalse(tg.contains(b2, tg.Box2I(-1, -1, 1, 1)))
        self.assertTrue(tg.contains(b2, tg.V2I(1, 1)))
        self.assertFalse(tg.contains(b2, tg.V2I(-1, -1)))
        
        b2 = tg.Box2F(0, 0, 2, 2)
        self.assertTrue(tg.contains(b2, tg.Box2F(0, 0, 1, 1)))
        self.assertFalse(tg.contains(b2, tg.Box2F(-1, -1, 1, 1)))
        self.assertTrue(tg.contains(b2, tg.V2F(1, 1)))
        self.assertFalse(tg.contains(b2, tg.V2F(-1, -1)))
        
        b2 = tg.Box2I(0, 0, 3, 3)
        self.assertTrue(tg.intersects(b2, tg.Box2I(-1, -1, 2, 2)))
        self.assertFalse(tg.intersects(b2, tg.Box2I(-2, -2, 2, 2)))
        b2a = tg.intersect(b2, tg.Box2I(-1, -1, 2, 2))
        self.assertEqual(tg.Box2I(0, 0, 1, 1), b2a)

        b2 = tg.Box2F(0, 0, 2, 2)
        self.assertTrue(tg.intersects(b2, tg.Box2F(-1, -1, 2, 2)))
        self.assertFalse(tg.intersects(b2, tg.Box2F(-2, -2, 1, 1)))
        b2a = tg.intersect(b2, tg.Box2F(-1, -1, 2, 2))
        self.assertEqual(tg.Box2F(0, 0, 1, 1), b2a)
        
        b2 = tg.Box2I(1, 2, 3, 4)
        b2a = tg.expand(b2, tg.Box2I(1, 2, 4, 5))
        b2b = tg.expand(b2, tg.V2I(4, 5))
        self.assertEqual(tg.Box2I(1, 2, 4, 5), b2a)
        self.assertEqual(tg.Box2I(1, 2, 4, 4), b2b)
        
        b2 = tg.Box2I(1, 2, 3, 4)
        b2a = tg.margin(b2, tg.V2I(1, 2))
        b2b = tg.margin(b2, 1)
        b2c = tg.margin(b2, 1, 2, 3, 4)
        self.assertEqual(tg.Box2I(0, 0, 5, 8), b2a)
        self.assertEqual(tg.Box2I(0, 1, 5, 6), b2b)
        self.assertEqual(tg.Box2I(0, 0, 7, 10), b2c)

    def test_operators(self):
        self.assertEqual(tg.Box2I(1, 2, 3, 4), tg.Box2I(1, 2, 3, 4))
        self.assertNotEqual(tg.Box2I(1, 2, 3, 4), tg.Box2I(4, 3, 2, 1))

if __name__ == '__main__':
    unittest.main()
