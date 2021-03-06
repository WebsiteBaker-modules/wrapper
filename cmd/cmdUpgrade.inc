<?php
/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * cmdUpgrade.php
 *
 * @category     Addons
 * @package      Addons_wrapper
 * @copyright    Manuela v.d.Decken <manuela@isteam.de>
 * @author       Manuela v.d.Decken <manuela@isteam.de>
 * @license      http://www.gnu.org/licenses/gpl.html   GPL License
 * @version      3.0.1
 * @lastmodified $Date: 2017-03-03 23:14:28 +0100 (Fr, 03. Mrz 2017) $
 * @since        File available since 2015-12-17
 * @description  xyz
 */
/* -------------------------------------------------------- */
// Must include code to stop this file being accessed directly
if (!defined('WB_PATH')) { throw new Exception('Cannot access the addon \"'.basename(__DIR__).'\" directly'); }
/* -------------------------------------------------------- */

    $sSqlDumpFile = $sAddonPath.'/install-struct.sql';
    if (is_readable($sSqlDumpFile)) {
        // upgrade database tables
        $database->SqlImport($sSqlDumpFile, TABLE_PREFIX, __FILE__);
    }
// sanitize mod_wrapper.url
    $msg = '';
    $sql = 'SELECT `section_id`, `url` FROM `'.TABLE_PREFIX.'mod_wrapper` '
         . 'WHERE `url` NOT LIKE \'http%\'';
    if (($oInstances = $database->query($sql))) {
        while (($aInstance = $oInstances->fetchRow(MYSQLI_ASSOC))) {
            // add WB_URL to relative URLs
            $sNewUrl = WB_URL.'/'.ltrim($aInstance['url'], '\\/');
            $sql = 'UPDATE `'.TABLE_PREFIX.'mod_wrapper` '
                 . 'SET `url`=\''.$database->escapeString($sNewUrl).'\' '
                 . 'WHERE `section_id`='.(int)$aInstance['section_id'];
            if (!$database->query($sql)) {
                $msg = $database->get_error();
                break;
            }
        }
    } else { $msg = $database->get_error(); }
// replace local host by SYSVAR-Tag in mod_wrapper.url
    $sql = 'SELECT `section_id`, `url` FROM `'.TABLE_PREFIX.'mod_wrapper`';
    if (($oInstances = $database->query($sql))) {
        while (($aInstance = $oInstances->fetchRow(MYSQLI_ASSOC))) {
            // add WB_URL to relative URLs
            $sNewUrl = preg_replace(
                '/^'.preg_quote(str_replace('\\', '/', WB_URL).'/', '/').'/si',
                '{SYSVAR:AppUrl}',
                ltrim(str_replace('\\', '/', $aInstance['url']), '/')
            );
            $sql = 'UPDATE `'.TABLE_PREFIX.'mod_wrapper` '
                 . 'SET `url`=\''.$database->escapeString($sNewUrl).'\' '
                 . 'WHERE `section_id`='.(int)$aInstance['section_id'];
            if (!$database->query($sql)) {
                $msg = $database->get_error();
                break;
            }
        }
    } else { $msg = $database->get_error(); }

// end of file

