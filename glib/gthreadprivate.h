/* GLIB - Library of useful routines for C programming
 *
 * gthreadprivate.h - GLib internal thread system related declarations.
 *
 *  Copyright (C) 2003 Sebastian Wilhelmi
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __G_THREADPRIVATE_H__
#define __G_THREADPRIVATE_H__

#include "deprecated/gthread.h"
#include "ghash.h"

typedef struct _GRealThread GRealThread;
typedef struct _GThreadBeacon GThreadBeacon;

struct  _GRealThread
{
  GThread thread;

  gint ref_count;
  gboolean ours;
  gchar *name;
  gpointer retval;
  GThreadBeacon *lifetime_beacon;
  GHashTable *pending_garbage;
  gboolean destructor_registered;
};

/* system thread implementation (gthread-posix.c, gthread-win32.c) */
void            g_system_thread_wait            (GRealThread  *thread);

GRealThread *   g_system_thread_new             (GThreadFunc   func,
                                                 gulong        stack_size,
                                                 GError      **error);
void            g_system_thread_free            (GRealThread  *thread);

void            g_system_thread_exit            (void);
void            g_system_thread_set_name        (const gchar  *name);


/* gthread.c */
GThread *       g_thread_new_internal           (const gchar  *name,
                                                 GThreadFunc   proxy,
                                                 GThreadFunc   func,
                                                 gpointer      data,
                                                 gsize         stack_size,
                                                 GError      **error);

gpointer        g_thread_proxy                  (gpointer      thread);

void            g_thread_perform_cleanup        (gpointer      thread);
void            g_thread_schedule_cleanup       (gpointer      thread);
void            g_thread_private_destroy_later  (GPrivate     *key,
                                                 gpointer      value);

GThreadBeacon * g_thread_lifetime_beacon_new    (void);
void            g_thread_lifetime_beacon_free   (GThreadBeacon *beacon);
gboolean        g_thread_lifetime_beacon_check  (GThreadBeacon *beacon);

#endif /* __G_THREADPRIVATE_H__ */
