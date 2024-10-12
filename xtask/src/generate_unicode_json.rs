use std::{fs, path::Path, process::Command};

use anyhow::{anyhow, Result};
use lazy_static::lazy_static;
use serde_json::{json, to_string, Value};

const CATEGORY_OUTPUT_PATH: &str = "cli/generate/src/prepare_grammar/unicode-categories.json";
const PROPERTY_OUTPUT_PATH: &str = "cli/generate/src/prepare_grammar/unicode-properties.json";
const CATEGORY_ALIAS_OUTPUT_PATH: &str =
    "cli/generate/src/prepare_grammar/unicode-category-aliases.json";
const PROPERTY_ALIAS_OUTPUT_PATH: &str =
    "cli/generate/src/prepare_grammar/unicode-property-aliases.json";

const UNICODE_STANDARD_VERSION: &str = "15.1.0";

lazy_static! {
    static ref CATEGORY_URL: String =
        format!("https://unicode.org/Public/{UNICODE_STANDARD_VERSION}/ucd/UnicodeData.txt");
    static ref PROPERTY_URL: String =
        format!("https://unicode.org/Public/{UNICODE_STANDARD_VERSION}/ucd/PropList.txt");
    static ref DERIVED_PROPERTY_URL: String = format!(
        "https://unicode.org/Public/{UNICODE_STANDARD_VERSION}/ucd/DerivedCoreProperties.txt"
    );
    static ref CATEGORY_ALIAS_URL: String = format!(
        "https://unicode.org/Public/{UNICODE_STANDARD_VERSION}/ucd/PropertyValueAliases.txt"
    );
    static ref PROPERTY_ALIAS_URL: String =
        format!("https://unicode.org/Public/{UNICODE_STANDARD_VERSION}/ucd/PropertyAliases.txt");
    static ref EMOJI_DATA_URL: String =
        format!("https://unicode.org/Public/{UNICODE_STANDARD_VERSION}/ucd/emoji/emoji-data.txt");
}

fn cached_download(url: &str) -> String {
    println!("Downloading {url}");
    let (_, filename) = url.rsplit_once('/').unwrap();
    let (filename, ext) = filename.split_once('.').unwrap();
    let download_path = Path::new("target")
        .join("tmp")
        .join(format!("{filename}.{UNICODE_STANDARD_VERSION}.{ext}"));

    if download_path.exists() {
        fs::read_to_string(&download_path).unwrap()
    } else {
        let output = Command::new("curl")
            .arg(url)
            .output()
            .expect("Failed to execute curl");

        let data = String::from_utf8_lossy(&output.stdout).to_string();
        fs::write(&download_path, &data).unwrap();
        data
    }
}

pub fn run() -> Result<()> {
    let category_data = cached_download(&CATEGORY_URL);
    let property_data = cached_download(&PROPERTY_URL);
    let derived_property_data = cached_download(&DERIVED_PROPERTY_URL);
    let category_alias_data = cached_download(&CATEGORY_ALIAS_URL);
    let property_alias_data = cached_download(&PROPERTY_ALIAS_URL);
    let emoji_data = cached_download(&EMOJI_DATA_URL);

    let properties = parse_properties(&format!(
        "{property_data}{derived_property_data}{emoji_data}"
    ))?;
    let categories = parse_categories(&category_data)?;
    let property_aliases = parse_property_aliases(&property_alias_data)?;
    let category_aliases = parse_category_aliases(&category_alias_data)?;

    fs::write(PROPERTY_OUTPUT_PATH, to_string(&properties)?)?;
    fs::write(CATEGORY_OUTPUT_PATH, to_string(&categories)?)?;
    fs::write(PROPERTY_ALIAS_OUTPUT_PATH, to_string(&property_aliases)?)?;
    fs::write(CATEGORY_ALIAS_OUTPUT_PATH, to_string(&category_aliases)?)?;

    Ok(())
}

fn parse_properties(data: &str) -> Result<Value> {
    let mut properties = json!({});
    let mut row = 0;
    let mut line_start = 0;
    let mut line_end = 0;
    let len = data.len();

    while line_start < len {
        row += 1;
        line_start = if line_end == 0 { 0 } else { line_end + 1 };
        line_end = data[line_start..]
            .find('\n')
            .map_or(len, |i| line_start + i);

        if line_end == len {
            break;
        }

        // Skip over blank and comment lines
        if data[line_start..line_end].trim().is_empty()
            || data[line_start..line_end].starts_with('#')
        {
            continue;
        }

        // Parse the first two semicolon fields:
        // * code point or code point range
        // * property
        let code_point_end = data[line_start..].find(';').map_or(len, |i| line_start + i);
        let property_start = code_point_end + 1;
        let property_end = data[property_start..]
            .find('#')
            .map_or(len, |i| property_start + i);

        if code_point_end == len || property_end == len {
            return Err(anyhow!("Unexpected format on line {row}"));
        }

        // Process ranges (separated by '..')
        let code_point_ranges = data[line_start..code_point_end].trim();
        println!("Data: {code_point_ranges}");
        let code_points = code_point_ranges
            .split("..")
            .map(|p| u32::from_str_radix(p.trim(), 16).unwrap())
            .collect::<Vec<u32>>();
        let code_points = if code_points.len() == 1 {
            vec![code_points[0], code_points[0]]
        } else {
            code_points
        };

        let property = data[property_start..property_end].trim().to_string();

        println!("Property: {code_points:?}, {property:?}");

        let obj = properties.as_object_mut().unwrap();
        let entry = obj
            .entry(property.clone())
            .or_insert(json!([]))
            .as_array_mut()
            .unwrap();
        entry.push(Value::from(code_points[0]));
        entry.push(Value::from(code_points[1]));
    }

    Ok(properties)
}

fn parse_categories(data: &str) -> Result<Value> {
    let mut categories = json!({});
    let mut row = 0;
    let mut line_start = 0;
    let mut line_end = 0;
    let len = data.len();

    while line_start < len {
        row += 1;
        line_start = if line_end == 0 { 0 } else { line_end + 1 };
        line_end = data[line_start..]
            .find('\n')
            .map_or(len, |i| line_start + i);

        if line_end == len {
            break;
        }

        let code_point_end = data[line_start..]
            .find(';')
            .map_or(line_end, |i| line_start + i);
        let name_start = code_point_end + 1;
        let name_end = data[name_start..]
            .find(';')
            .map_or(line_end, |i| name_start + i);
        let category_start = name_end + 1;
        let category_end = data[category_start..]
            .find(';')
            .map_or(line_end, |i| category_start + i);

        if name_start == 0 || category_start == 0 || category_end == line_end {
            return Err(anyhow!("Unexpected format on line {row}"));
        }

        let code_point = u32::from_str_radix(&data[line_start..code_point_end], 16)
            .map_err(|_| anyhow!("Invalid code point on line {row}"))?;
        let name = &data[name_start..name_end];
        let category = &data[category_start..category_end];

        println!("Category: {code_point} {category} {name}");

        let obj = categories.as_object_mut().unwrap();
        let entry = obj
            .entry(category)
            .or_insert(json!([]))
            .as_array_mut()
            .unwrap();
        entry.push(Value::from(code_point));
    }

    Ok(categories)
}

fn parse_property_aliases(data: &str) -> Result<Value> {
    let mut property_aliases = json!({});
    let mut row = 0;
    let mut line_start = 0;
    let mut line_end = 0;
    let len = data.len();

    while line_start < len {
        row += 1;
        line_start = if line_end == 0 { 0 } else { line_end + 1 };
        line_end = data[line_start..]
            .find('\n')
            .map_or(len, |i| line_start + i);

        if line_end == len {
            break;
        }

        // Skip over blank and comment lines
        if data[line_start..line_end].trim().is_empty()
            || data[line_start..line_end].starts_with('#')
        {
            continue;
        }

        // Parse the first two semicolon fields:
        // * short name
        // * long name
        let short_name_end = data[line_start..line_end]
            .find(';')
            .map(|i| line_start + i)
            .ok_or_else(|| anyhow!("Unexpected format on line {row}"))?;
        let long_name_start = short_name_end + 1;

        if long_name_start == 0 {
            return Err(anyhow!("Unexpected format on line {row}"));
        }

        let mut alias = data[line_start..short_name_end].trim().to_string();
        let mut long_name = None::<String>;
        let mut name_start = long_name_start;
        let mut line_done = false;

        while !line_done {
            let name_end = data[name_start..line_end]
                .find(';')
                .or_else(|| data[name_start..line_end].find('#'))
                .map_or(line_end, |i| name_start + i);

            if name_end == line_end {
                line_done = true;
            }

            if long_name.is_none() {
                long_name = Some(data[name_start..name_end].trim().to_string());
            } else {
                alias = data[name_start..name_end].trim().to_string();
            }

            println!(
                "Property alias: {alias} {}",
                long_name.as_deref().unwrap_or("")
            );

            let obj = property_aliases.as_object_mut().unwrap();
            obj.insert(
                alias.clone(),
                Value::from(long_name.clone().unwrap_or_default()),
            );
            name_start = name_end + 1;
        }
    }

    Ok(property_aliases)
}

fn parse_category_aliases(data: &str) -> Result<Value> {
    let mut category_aliases = json!({});
    let mut row = 0;
    let mut line_start = 0;
    let mut line_end = 0;
    let len = data.len();

    while line_start < len {
        row += 1;
        line_start = if line_end == 0 { 0 } else { line_end + 1 };
        line_end = data[line_start..]
            .find('\n')
            .map_or(len, |i| line_start + i);

        if line_end == len {
            break;
        }

        // Skip over blank and comment lines
        if data[line_start..line_end].trim().is_empty()
            || data[line_start..line_end].starts_with('#')
        {
            continue;
        }

        // Parse the first three semicolon-separated fields:
        let property_value_type_end = data[line_start..].find(';').map_or(len, |i| line_start + i);
        let short_name_start = property_value_type_end + 1;
        let short_name_end = data[short_name_start..]
            .find(';')
            .map_or(len, |i| short_name_start + i);
        let long_name_start = short_name_end + 1;

        if short_name_start == 0 || long_name_start == 0 {
            return Err(anyhow!("Unexpected format on line {row}"));
        }

        let property_value_type = data[line_start..property_value_type_end].trim().to_string();
        let short_name = data[short_name_start..short_name_end].trim().to_string();

        // Filter for General_Category lines
        if property_value_type != "gc" {
            continue;
        }

        let mut alias_start = long_name_start;
        let mut line_done = false;
        while !line_done {
            let alias_end = data[alias_start..]
                .find(';')
                .map_or(len, |i| alias_start + i);
            let mut final_alias_end = if alias_end > line_end {
                data[alias_start..]
                    .find('#')
                    .map_or(line_end, |i| alias_start + i)
            } else {
                alias_end
            };

            if final_alias_end > line_end {
                final_alias_end = line_end;
                line_done = true;
            }

            let alias = data[alias_start..final_alias_end].trim().to_string();
            println!("Category alias: {alias}, {short_name}");
            let obj = category_aliases.as_object_mut().unwrap();
            obj.insert(alias, Value::from(short_name.clone()));
            alias_start = final_alias_end + 1;
        }
    }

    Ok(category_aliases)
}
